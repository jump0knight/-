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
    void setupPlot();
private slots:
    void on_btn_open_serial_clicked();

    void on_btn_close_serial_clicked();

    void readbuf();

    void on_receive_cleanButton_clicked();

    void on_send_cleanButton_clicked();

    void on_sendButton_clicked();

    void myMove(QMouseEvent *e);

    void addDataToGraph(double x, double y);

    void on_gstop1_Button_clicked();

    void on_gstart1_Button_clicked();

    void on_gclear1_Button_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *Serialport;
    QCPItemTracer *tracer = nullptr;     // 游标
    QCPItemText *tracerLabel = nullptr;  // 游标说明

    QByteArray receivedData;  // 存储接收到的数据

    void ScanSerialport();
    void InitCombox();
};
#endif // MAINWINDOW_H
