struct kd_node {
	int leaf_node; // 1 if leaf, 0 if internal node
	int cut_dim; // cutting dimension
	float cut_val; // cutting value
	kd_node *lo_child, *hi_child; // low and high children
	int pt; // data point index
}

typedef float Point[d]; // point data type

Point points[n]; // data point storage
Point q; // query point
float off[d]; // array of offsets
float nn_dist; // best squared distance so far

float kd_standard(
	Point qq, // query point
	kd_node* root) // root of kd tree
{
	q = qq; // save query point
	nn_dist = HUGE; // initial distance
	
	for (int i = 0; i < d; i++) // initialize offsets
		off[i] = 0.0;
	
	rkd(root, 0.0); // search the tree
	return nn_dist;
}

void rkd( // recursive search procedure
	kd_node* u, // current node
	float rd) // squared dist to this rect
{
	if (u->leaf_node) { // at a leaf bucket
		nn_dist = min(nn_dist, // use this point if closer
		dist2(q, points[u->pt]));
	}
	else { // internal node
		int cd = u->cut_dim; // cutting dimension
		float old_off = off[cd]; // save old offset
		float new_off = q[cd] - u->cut_val; // offset to further child
		
		if (new_off < 0) { // left of cutting plane
			rkd(u->lo_child, rd); // search closer subtree first
			rd += - old_off*old_off // distance to further child
			+ new_off*new_off;
			
			if (rd < nn_dist) { // close enough to consider?
				off[cd] = new_off; // update offset
				rkd(u->hi_child, rd); // search further subtree
				off[cd] = old_off; // restore offset
			}
		}
		else { // q is above cutting plane
			...analogous with lo_child and hi_child interchanged...
		}
	}
}

float kd_priority(
	Point q, // query point
	kd_node* root) // root of kd tree
{
	Priority_Queue Q;
	float nn_dist = HUGE; // initial distance
	kd_node* u;
	float rd; // distance to rectangle
	Q.Insert(root, 0.0); // start with root of tree
	
	while (Q.NotEmpty()) { // repeat until queue is empty
		Q.Extr_Min(u, rd); // closest node to query point
		if (rd >= nn_dist) // further from nearest so far
			break;
		while (!u->leaf_node) { // descend until leaf found
			int cd = u->cut_dim; // cutting dimension
			float old_off, new_rd;
			float new_off = q[cd] - u->cut_val; // offset to further child
			
			if (new_off < 0) { // q is below cutting plane
				old_off = q[cd] - u->low_val; // compute offset
				
				if (old_off > 0) // overlaps interval
					old_off = 0;
					
				new_rd = rd - old_off*old_off // distance to further child
						 + new_off*new_off;
				Q.Insert(u->hi_child, new_rd); // enqueue hi_child for later
				u = u->lo_child; // visit lo_child next
			}
			else { // q is above cutting plane
				old_off = q[cd] - u->low_val; // compute offset
				
				if (old_off > 0) // overlaps interval
					old_off = 0;
					
				new_rd = rd - old_off*old_off // distance to further child
				+ new_off*new_off;
				Q.Insert(u->hi_child, new_rd); // enqueue hi_child for later
				u = u->lo_child; // visit lo_child nextold_off = q[cd] - u->low_val; // compute offset
				
				if (old_off > 0) // overlaps interval
					old_off = 0;
					
				new_rd = rd - old_off*old_off // distance to further child
				+ new_off*new_off;
				Q.Insert(u->hi_child, new_rd); // enqueue hi_child for later
				u = u->lo_child; // visit lo_child next
			}
		}
		nn_dist = min(nn_dist, // leaf - use point if closer
		dist2(points[u->pt], q));
	}
	return nn_dist;
}
