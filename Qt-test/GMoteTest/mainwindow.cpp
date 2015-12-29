#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image = new QPixmap;
    scene = new QGraphicsScene(this);

    serial = new QSerialPort(QString("COM3"));
    serial->setBaudRate(2000000);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);

    if(serial->open(QIODevice::ReadOnly))
        qDebug() << "Serial port Opened";
    else
         qDebug() << "Serial port not opened";


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

    connect(ui->gestureListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setImage()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialReceive()));

    ui->result->setText("LOL!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage()
{
    int i = ui->gestureListWidget->currentRow();

    image->load(gestList[i].fileName);

    scene->clear();
    scene->addPixmap(*image);
    scene->setSceneRect(image->rect());

    ui->gestureView->setScene(scene);
    ui->gestureView->show();
}

void MainWindow::serialReceive()
{
    QByteArray received = serial->readAll();
    QString str(received);

    if(gestList[ui->gestureListWidget->currentRow()].cmd == str){
        ui->result->setText("Correct!");
    }
    else
        ui->result->setText("Incorrect!");
}
