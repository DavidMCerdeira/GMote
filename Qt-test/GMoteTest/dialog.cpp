#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

Dialog::Dialog(QSerialPort *serial, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->serial = serial;

    qDebug() << "Dialog Serial: " << serial;
     foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
         ui->comboBox->addItem(info.portName());
     }

     connect(this, SIGNAL(accepted()), this, SLOT(serialConnect()));
     connect(this, SIGNAL(rejected()), this, SLOT(close()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::serialConnect()
{
    qDebug() << "Serial Connect " << ui->comboBox->currentText();
    serial->setPortName(ui->comboBox->currentText());
    serial->setBaudRate(2000000);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

    qDebug() << ((serial->isOpen()) ? "true" : "false");
}
