#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter=0;
    QTimer1 = new QTimer(this);
    connect(QTimer1, &QTimer::timeout, this, &MainWindow::onQTimer1);
    QPaintBox1 = new QPaintBox(0, 0, ui->widget);
}

MainWindow::~MainWindow()
{
    delete QTimer1;

    delete ui;
}


void MainWindow::onQTimer1(){
    QDateTime dt;
    float aRad;
    int hour, minutes, seconds, mSecs, xi, xf, yi, yf, w, h, radius;
    int aux1, aux2;

    QPen pen;
    QBrush brush;
    QPainter paint(QPaintBox1->getCanvas());

    counter++;
    if(counter==100)
        counter=0;

    ui->lcdNumber->display(QString("%1").arg(counter, 4, 10, QChar('0')));
    ui->lineEdit->setText(dt.currentDateTime().toString("hh:mm:ss.zzz-dd/MM/yyyy"));

    hour = dt.currentDateTime().time().hour();
    minutes = dt.currentDateTime().time().minute();
    seconds = dt.currentDateTime().time().second();
    mSecs = dt.currentDateTime().time().msec();

    pen.setWidth(5);
    pen.setColor(Qt::yellow);
    paint.setPen(pen);
    brush.setColor(Qt::darkGray);
    brush.setStyle(Qt::SolidPattern);
    paint.setBrush(brush);
    paint.drawEllipse(5, 5, 401, 401);

    pen.setColor(Qt::white);
    pen.setWidth(3);
    paint.setPen(pen);
    for(int i= 0; i<360; i+=6){
        aRad = i*M_PI/180;
        if(!(i%30)){
            xi = 206+175*cos(aRad);
            yi = 206-175*sin(aRad);
        }else{
            xi = 206+185*cos(aRad);
            yi = 206-185*sin(aRad);
        }
        xf = 206+190*cos(aRad);
        yf = 206-190*sin(aRad);
        paint.drawLine(xi, yi, xf, yf);
    }

    aRad = (90-(6*seconds+0.006*mSecs))*M_PI/180;
        xf = 206+196*cos(aRad);
        yf = 206-196*sin(aRad);
        aux1 = 206+170*cos(aRad);
        aux2 = 206-170*sin(aRad);
        pen.setColor(Qt::darkRed);
        pen.setWidth(5);
        paint.setPen(pen);
        paint.drawLine(aux1, aux2, xf, yf);

        aRad = (90-(6*minutes+0.1*seconds))*M_PI/180;
        xf = 206+155*cos(aRad);
        yf = 206-155*sin(aRad);
        aux1 = 206-20*cos(aRad);
        aux2 = 206+20*sin(aRad);
        pen.setColor(Qt::yellow);
        pen.setWidth(4);
        paint.setPen(pen);
        paint.drawLine(aux1, aux2, xf, yf);

        if(hour <12){
            hour -= 12;
            aRad = (90-(30*hour)+0.5*minutes)*M_PI/180;
        }else{
            aRad = (90-(30*hour)-0.5*minutes)*M_PI/180;
        }
        xf = 206+115*cos(aRad);
        yf = 206-115*sin(aRad);
        aux1 = 206-20*cos(aRad);
        aux2 = 206+20*sin(aRad);
        pen.setColor(Qt::yellow);
        pen.setWidth(4);
        paint.setPen(pen);
        paint.drawLine(aux1, aux2, xf, yf);

        pen.setColor(Qt::black);
        pen.setWidth(2);
        paint.setPen(pen);
        brush.setColor(Qt::black);
        brush.setStyle(Qt::SolidPattern);
        paint.setBrush(brush);
        paint.drawEllipse(203, 203, 5, 5);

    QPaintBox1->update();
}

void MainWindow::on_pushButton_clicked()
{
    if(QTimer1->isActive()){
        QTimer1->stop();
        ui->pushButton->setText("ON");
    }else{
        QTimer1->start(100);
        ui->pushButton->setText("OFF");
    }
}


void MainWindow::on_pushButton_2_clicked()
{   

//    pen.setColor(Qt::red);
//    paint.drawLine(0, QPaintBox1->height()/2, QPaintBox1->width(), QPaintBox1->height()/2);

//    w = QPaintBox1->width();
//    h = QPaintBox1->height();
//    radius = w/2;
//    if(h < w)
//        radius = h/2;

//    paint.drawEllipse(w/2-radius, h/2-radius, 2*radius, 2*radius);
    QPaintBox1->getCanvas()->fill(Qt::black);
    QPaintBox1->update();
}


