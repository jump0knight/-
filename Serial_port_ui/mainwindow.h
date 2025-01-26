#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QWidget>
#include <QSerialPort>
#include <QTextBrowser>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupPlot1();
    void setupPlot2();
    void setupPlot3();
private slots:
    void on_btn_open_serial_clicked();

    void on_btn_close_serial_clicked();

    void readbuf();

    void on_receive_cleanButton_clicked();

    void on_send_cleanButton_clicked();

    void on_sendButton_clicked();

    void myMove1(QMouseEvent *e);
    void myMove2(QMouseEvent *e);
    void myMove3(QMouseEvent *e);

    void on_gstop1_Button_clicked();

    void on_gstart1_Button_clicked();

    void on_gclear1_Button_clicked();

    void on_gclear2_Button_clicked();

    void on_gstart2_Button_clicked();

    void on_gstop2_Button_clicked();

    void on_gstart3_Button_clicked();

    void on_gstop3_Button_clicked();

    void on_gclear3_Button_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *Serialport;
//    QCPItemTracer *tracer = nullptr;     // 游标
//    QCPItemText *tracerLabel = nullptr;  // 游标说明

    QCPItemTracer *tracer1, *tracer2, *tracer3;
    QCPItemText *tracerLabel1, *tracerLabel2, *tracerLabel3;

    QByteArray receivedData;  // 存储接收到的数据
    QByteArray receivedData1;  // 存储接收到的数据
    QByteArray receivedData2;  // 存储接收到的数据
    QByteArray receivedData3;  // 存储接收到的数据

    void ScanSerialport();
    void InitCombox();
};
#endif // MAINWINDOW_H
