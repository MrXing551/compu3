#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aux=0;
    QTimer1 = new QTimer(this);
    connect(QTimer1, &QTimer::timeout, this, &MainWindow::onQTimer1);
    QPaintBox1 = new QPaintBox(0, 0, ui->widget);

}

MainWindow::~MainWindow()
{
    delete QTimer1;

    delete ui;
}

void MainWindow::drawClock(int hour, int minutes, int seconds, int mSecs, int simple){
    float aRad;
    int xi, xf, yi, yf, centerX, centerY, diameter, dotDiameter, hourL, minuteL, secondsL, hourLB, minuteLB, secondsLB;
    QPen pen;
    QBrush brush;
    QPainter paint(QPaintBox1->getCanvas());

//Tamaños del reloj:
    centerX = 206; //(QPaintBox1->width()/2);
    centerY = 206; //(QPaintBox1->height()/2);
    diameter = QPaintBox1->width()-10;
//Elijo el estilo del reloj:
    if(simple){
    //Largo de las agujas:
        secondsL = 190;
        secondsLB = 165;
        minuteL = 155;
        minuteLB = 0;
        hourL = 115;
        hourLB = 0;
    //Contorno y fondo del reloj:
        pen.setWidth(0);
        pen.setColor(QColorConstants::Black);
        brush.setColor(QColorConstants::Black);
    }else{
    //Largo de las agujas:
        secondsL = 190;
        secondsLB = -20;
        minuteL = 155;
        minuteLB = 20;
        hourL = 115;
        hourLB = 20;
    //Diámetro del punto central:
        dotDiameter = 5;
    //Contorno y fondo del reloj:
        pen.setWidth(5);
        pen.setColor(QColorConstants::Yellow);
        brush.setColor(QColorConstants::DarkGray);
    }

//Contorno y fondo del reloj:
        brush.setStyle(Qt::SolidPattern);
        paint.setPen(pen);
        paint.setBrush(brush);
        paint.drawEllipse(5, 5, diameter, diameter);



//Líneas del Reloj:
    if(simple){
        pen.setWidth(4);
        pen.setColor(QColorConstants::Cyan);
    }else{
        pen.setWidth(3);
        pen.setColor(QColorConstants::White);
    }
    paint.setPen(pen);
    for(int i= 0; i<360; i+=6){
        aRad = i*M_PI/180;
        if(!(i%30)){
            xi = centerX+175*cos(aRad);
            yi = centerY-175*sin(aRad);
        }else{
            xi = centerX+185*cos(aRad);
            yi = centerY-185*sin(aRad);
        }
        xf = centerX+190*cos(aRad);
        yf = centerY-190*sin(aRad);
        paint.drawLine(xi, yi, xf, yf);
    }
//Segundos:
    aRad = (90-(6*seconds+0.006*mSecs))*M_PI/180;
        xf = centerX+secondsL*cos(aRad);
        yf = centerY-secondsL*sin(aRad);
        xi = centerX+secondsLB*cos(aRad);
        yi = centerY-secondsLB*sin(aRad);
        if(simple){
            pen.setColor(QColorConstants::Red);
            pen.setWidth(5);
        }else{
            pen.setColor(QColorConstants::DarkRed);
            pen.setWidth(4);
        }
        paint.setPen(pen);
        paint.drawLine(xi, yi, xf, yf);
//Minutos:
        aRad = (90-(6*minutes+0.1*seconds))*M_PI/180;
        xf = centerX+minuteL*cos(aRad);
        yf = centerY-minuteL*sin(aRad);
        if(simple){
            pen.setColor(QColorConstants::Cyan);
        }else{
            pen.setColor(QColorConstants::Yellow);
        }
        xi = centerX-minuteLB*cos(aRad);
        yi = centerY+minuteLB*sin(aRad);

        pen.setWidth(4);
        paint.setPen(pen);
        paint.drawLine(xi, yi, xf, yf);
//Hora:
            aRad = (90-(30*hour)-0.5*minutes)*M_PI/180;
            xf = centerX+hourL*cos(aRad);
            yf = centerY-hourL*sin(aRad);
            if(simple){
                pen.setColor(QColorConstants::Cyan);
                pen.setWidth(6);
            }else{
                pen.setColor(QColorConstants::Yellow);
                pen.setWidth(4);
            }
            xi = centerX-hourLB*cos(aRad);
            yi = centerY+hourLB*sin(aRad);
            paint.setPen(pen);
            paint.drawLine(xi, yi, xf, yf);


//Punto central
        if(!simple){
            pen.setColor(QColorConstants::Black);
            pen.setWidth(2);
            paint.setPen(pen);
            brush.setColor(QColorConstants::Black);
            brush.setStyle(Qt::SolidPattern);
            paint.setBrush(brush);
            paint.drawEllipse(centerX-3, centerY-3, dotDiameter, dotDiameter);
        }

    QPaintBox1->update();
    qDebug("%i, %i, %i", centerX, centerY, simple);
}


void MainWindow::onQTimer1(){
    QDateTime dt;
    int hour, minutes, seconds, mSecs;

    hour = dt.currentDateTime().time().hour();
    minutes = dt.currentDateTime().time().minute();
    seconds = dt.currentDateTime().time().second();
    mSecs = dt.currentDateTime().time().msec();

    ui->lineEdit->setText(dt.currentDateTime().toString("hh:mm:ss.zzz - dd/MM/yyyy"));

    if(mSecs<500)
        ui->lcdNumber->display(dt.currentDateTime().toString("hh:mm"));
    else
        ui->lcdNumber->display(dt.currentDateTime().toString("hh mm"));


    drawClock(hour, minutes, seconds, mSecs, simple);
}

void MainWindow::on_pushButton_clicked()
{
    if(QTimer1->isActive()){
        QTimer1->stop();
        ui->pushButton->setText("ON");
    }else{
        QTimer1->start(16);
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
    if(simple!=1){
        simple=1;
    }else{
        simple=0;
    }
}


