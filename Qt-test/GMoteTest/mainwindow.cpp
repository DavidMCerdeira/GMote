#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i = 0; i < 7; i++)
       ui->gestureListWidget->insertItem(i, "Gesto " + QString::number(i) );

    connect(ui->gestureListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setImage()));

    ui->result->setText("LOL!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage()
{
    int i = ui->gestureListWidget->currentRow();
    QString file = ".png";
    if(i < 8)
        file.prepend(QString::number(i));

    QPixmap *image = new QPixmap;
    image->load(file);
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(*image);
    scene->setSceneRect(image->rect());

    ui->gestureView->setScene(scene);
    ui->gestureView->show();
}
