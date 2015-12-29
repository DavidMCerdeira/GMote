#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QtSerialPort/QSerialPort>

namespace Ui {
class MainWindow;
}

struct gesture{
    QString name;
    QString fileName;
    QString cmd;
    gesture(QString name, QString fileName, QString cmd)
        :name(name), fileName(fileName), cmd(cmd)
    {

    }
private:
    gesture();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap *image;
    QGraphicsScene* scene;

    QSerialPort* serial;

    QList<gesture> gestList;

public slots:
    void setImage();
    void serialReceive();
};

#endif // MAINWINDOW_H
