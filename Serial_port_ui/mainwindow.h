#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_btn_open_serial_clicked();

    void on_btn_close_serial_clicked();

    void readbuf();

    void on_receive_cleanButton_clicked();

    void on_send_cleanButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *Serialport;

    void ScanSerialport();
    void InitCombox();
};
#endif // MAINWINDOW_H
