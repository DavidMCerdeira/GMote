#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new QPixmap;
    scene = new QGraphicsScene(this);

    gestList.append(gesture("Pictures",   "0.png", "11"));
    gestList.append(gesture("Video",      "1.png", "12"));
    gestList.append(gesture("Music",      "2.png", "13"));
    gestList.append(gesture("Settings",   "3.png", "14"));
    gestList.append(gesture("Play/Pause", "4.png", "9"));
    //gestList.append(gesture("Fullscreen", "5.png", "10"));
    gestList.append(gesture("Next",       "6.png", "15"));
    gestList.append(gesture("Previous",   "7.png", "16"));

    for(int i = 0; i < gestList.length(); i++)
    {
        ui->gestureListWidget->insertItem(i, gestList[i].name);
    }

    ui->result->setText("");

    serial = new QSerialPort();

    dialog = new Dialog(serial);
    dialog->exec();

    if(serial == NULL)
        this->close();

    serial->open(QIODevice::ReadWrite);

    connect(ui->gestureListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setImageTraining()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceive()));
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

void MainWindow::setImageInteraction(QString fileName)
{
    image->load(fileName);
    scene->clear();
    scene->addPixmap(*image);
    scene->setSceneRect(image->rect());

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::serialReceive()
{
    QByteArray received = serial->readLine(10);
    received.remove(received.length()-1, 1);
    QString str(received);

    qDebug() << str;

    if(ui->tabWidget->currentIndex() == 0){
        if(gestList[ui->gestureListWidget->currentRow()].cmd == str){
            ui->result->setText("Correct!");
        }
        else
            ui->result->setText("Incorrect!");
    }
    else if(ui->tabWidget->currentIndex() == 1){
        QList<gesture>::iterator it = gestList.begin();
       while(it != gestList.end() && it->cmd != str){
           it++;
       }
       if(it == gestList.end()){
           qDebug() << "No gesture recognized...";
       }
       else if(it->cmd == str){ /* defensive condition */
           setImageInteraction("8.png");
       }
    }

}
