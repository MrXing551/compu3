#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <qpaintbox.h>
#include <QDateTime>
#include <math.h>
#include <qmath.h>
#include <QDebug>
#include <iostream>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onQTimer1();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void drawClock(int hour, int minutes, int seconds, int mSec, int simple);

private:
    Ui::MainWindow *ui;
    int aux, simple=0;

    QTimer *QTimer1;
    QPaintBox *QPaintBox1;
    QPolygon *QPolygon1;


};
#endif // MAINWINDOW_H
