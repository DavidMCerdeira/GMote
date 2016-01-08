#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QSerialPort *serial, QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSerialPort *serial;

private slots:
    void serialConnect();
};

#endif // DIALOG_H
