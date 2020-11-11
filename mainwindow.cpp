#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QtDebug>

QSerialPort *serial;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("/home/pi/Downloads/hellotest.jpeg");
    int w=ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this, SLOT(myfunction()));
    timer->start(2000);

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug()<< "Name :"<<info.portName();

    }

    serial= new QSerialPort(this);
//    serial->setPortName("ttyUSB0");
    serial->setPortName("COM2");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    serial->write("ok");
//    serial->close();
    connect(serial,SIGNAL(readyRead()), this,SLOT(serialReceived()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
    qDebug()<<"update..";
}

void MainWindow::on_pBConferma_clicked()
{
    QString conferma=ui->lE_SelPict->text();
    QString picture;

    if(conferma=="1")
        picture="/home/pi/Downloads/number_1.jpeg";
    else if(conferma=="2")
            picture="/home/pi/Downloads/number_2.jpeg";
    else if(conferma=="3")
            picture="/home/pi/Downloads/number_3.jpeg";
    else if(conferma=="4")
            picture="/home/pi/Downloads/number_4.jpeg";
    else if(conferma=="5")
            picture="/home/pi/Downloads/mosaico.jpeg";
    else if(conferma=="6")
            picture="/home/pi/Downloads/barre.jpeg";
    else if(conferma=="7")
            picture="/home/pi/Downloads/cinescopio.jpeg";

    QPixmap pix(picture);
    int w=ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::on_quit_clicked()
{
//   QMessageBox::about(this, "MioTitolo", "MioMessaggio") ;
    QApplication::quit();
}

void MainWindow::serialReceived()
{
    QString picture;
    QByteArray ba;
    char res=0;
    int returnval=0;

    ba=serial->readAll();
    returnval = VerChecksum(ba,&res);

    if(res==ba[2])
    {
        qDebug()<<"checksum OK!";
    }
    else{}

    ui->label_2->setText(ba);
    qDebug()<< ba;

    if((ba[1]& 0x07)== 1)
        picture=":/resources/Images/number_1.jpeg";
    else if((ba[1]& 0x07)== 2)
            picture=":/resources/Images/number_2.jpeg";
    else if((ba[1]& 0x07)== 3)
            picture=":/resources/Images/number_3.jpeg";
    else if((ba[1]& 0x07)== 4)
            picture=":/resources/Images/number_4.jpeg";
    else if((ba[1]& 0x07)== 5)
            picture=":/resources/Images/mosaico.jpeg";
    else if((ba[1]& 0x07)== 6)
            picture=":/resources/Images/barre.jpeg";
    else if((ba[1]& 0x07)== 7)
            picture=":/resources/Images/cinescopio.jpeg";

    QPixmap pix(picture);
    int w=ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

int MainWindow::VerChecksum(QByteArray bytesReceived, char* presult)
{
    int u8RetVal=0;

    *presult=~(bytesReceived[0]+bytesReceived[1])+1;

    return u8RetVal;
}


void MainWindow::on_pushButton_clicked()
{
}
