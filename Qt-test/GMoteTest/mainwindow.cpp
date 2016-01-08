#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new QPixmap;
    scene = new QGraphicsScene(this);

    gestList.append(gesture("Pictures",   "0.png", "A"));
    gestList.append(gesture("Video",      "1.png", "B"));
    gestList.append(gesture("Music",      "2.png", "C"));
    gestList.append(gesture("Settings",   "3.png", "D"));
    gestList.append(gesture("Play/Pause", "4.png", "E"));
    gestList.append(gesture("Next",       "5.png", "F"));
    gestList.append(gesture("Previous",   "6.png", "G"));

    for(int i = 0; i < gestList.length(); i++)
    {
        ui->gestureListWidget->insertItem(i, gestList[i].name);
    }

    ui->result->setText("");

    dialog = new Dialog(&serial);
    dialog->exec();

    serial.open(QIODevice::ReadWrite);


    connect(ui->gestureListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setImageTraining()));
    connect(&serial, SIGNAL(readyRead()), this, SLOT(serialReceive()));
    ui->gestureListWidget->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete image;
    delete scene;
    delete ui;
}

void MainWindow::setImageTraining()
{

    int i = ui->gestureListWidget->currentRow();

    image->load(gestList[i].fileName);

    scene->clear();
    scene->addPixmap(*image);
    scene->setSceneRect(image->rect());

    ui->gestureView->setScene(scene);
    ui->gestureView->show();

}

void MainWindow::setImageInteraction(gesture *gesture)
{
    image->load(gesture->fileName);
    scene->clear();
    scene->addPixmap(*image);
    scene->setSceneRect(image->rect());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::serialReceive()
{
    QByteArray received = serial.readAll();
    QString str(received);

    if(ui->tab->isEnabled()){
        if(gestList[ui->gestureListWidget->currentRow()].cmd == str){
            ui->result->setText("Correct!");
        }
        else
            ui->result->setText("Incorrect!");
    }
    else if(ui->tab_2->isEnabled()){
        QList<gesture>::iterator it;
       while(it != gestList.end() && it->cmd != str){
           it++;
       }
       if(it == gestList.end()){
           qDebug() << "No gesture recognized...";
       }
       else if(it->cmd == str){ /* defensive condition */
           setImageInteraction(&(*it));
       }
    }

}
