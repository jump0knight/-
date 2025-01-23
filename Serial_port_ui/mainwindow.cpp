#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QComboBox>
#include <QList>
#include <QString>
#include <QByteArray>
#include <QTextBrowser>
#include <QTextEdit>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(0,0,800,600);
    Serialport = new QSerialPort(this);

    InitCombox();

    ui->receive_text->setPlaceholderText("接收到的消息");
    ui->send_text->setPlaceholderText("发送的消息");

    connect(Serialport,SIGNAL(readyRead()),this,SLOT(readbuf()));

    ui->btn_close_serial->setEnabled(false);

    // 创建定时器来定期扫描串口
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::ScanSerialport);
    timer->start(500); // 每500毫秒扫描一次串口
}

void MainWindow::ScanSerialport(){
    QString selectedPort = ui->comboBox_port->currentText();  // 获取当前选中的串口
    bool isPortSelected = !selectedPort.isEmpty();

    // 清空组合框中的已有项目
    ui->comboBox_port->clear();

    //QSerialPortInfo类中，使用availablePorts函数可以查看当前所有可用串口，返回值类型为const QSerialPortInfo
    QList<QString> availablePorts;
    foreach (const QSerialPortInfo info, QSerialPortInfo::availablePorts()) {
        availablePorts.append(info.portName());        //将可用串口加入列表
        ui->comboBox_port->addItem(info.portName());        //调用addItem方法添加到下拉框中
    }

    // 如果当前选中的串口不在可用串口列表中，则认为连接断开，自动断开串口连接
    if (!availablePorts.contains(selectedPort)) {
        // 当前选中的串口不可用，断开连接
        if (Serialport->isOpen()) {
            Serialport->close(); // 关闭串口
            ui->btn_open_serial->setEnabled(true);
            ui->comboBox_boadrate->setEnabled(true);
            ui->comboBox_port->setEnabled(true);
            ui->btn_open_serial->setEnabled(true);
            ui->btn_close_serial->setEnabled(false);
        }
    }

    // 当前选中的串口不会被刷新掉
    if (isPortSelected)
    {
        ui->comboBox_port->setCurrentText(selectedPort);
    }
}

void MainWindow::InitCombox(){
    ui->comboBox_boadrate->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_open_serial_clicked()
{
    Serialport->setBaudRate(ui->comboBox_boadrate->currentText().toInt());
    Serialport->setPortName(ui->comboBox_port->currentText());
    //设置数据位

    /* 设置奇偶校验 */

    /* 设置停止位 */

    ui->btn_open_serial->setEnabled(false);
    ui->comboBox_boadrate->setEnabled(false);
    ui->comboBox_port->setEnabled(false);

    ui->btn_close_serial->setEnabled(true);

    Serialport->open(QIODevice::ReadWrite);//开启串口
}

void MainWindow::readbuf(){
    QByteArray buf = Serialport->readAll();
    ui->receive_text->insertPlainText(QString(buf));

    QTextCursor cursor = ui->receive_text->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->receive_text->setTextCursor(cursor);
}

//关闭串口
void MainWindow::on_btn_close_serial_clicked()
{
    Serialport->close();

    ui->btn_open_serial->setEnabled(true);
    ui->comboBox_boadrate->setEnabled(true);
    ui->comboBox_port->setEnabled(true);

    ui->btn_close_serial->setEnabled(false);
}

void MainWindow::on_receive_cleanButton_clicked()
{
    ui->receive_text->clear();
}

void MainWindow::on_send_cleanButton_clicked()
{
    ui->send_text->clear();
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->send_text->toPlainText();

    QByteArray data = text.toUtf8();
    Serialport->write(data);

    //qDebug() << "发送的原始数据: " << text;

    //qDebug() << "发送的数据（字节数组形式）: " << data;
}
