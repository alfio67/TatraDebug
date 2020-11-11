#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtDebug>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void myfunction();

private slots:
    void on_pushButton_clicked();

    void on_pBConferma_clicked();

    void on_quit_clicked();
private slots:
    void serialReceived();
    int VerChecksum(QByteArray bytesReceived, char* presult);


private:
    Ui::MainWindow *ui;
    QTimer *timer;


};

#endif // MAINWINDOW_H
