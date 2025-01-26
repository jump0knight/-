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

bool draw_data1 = 1;
bool draw_data2 = 1;
bool draw_data3 = 1;

int xCount1 = 0;  // 计数器用作x坐标
int xCount2= 0;  // 计数器用作x坐标
int xCount3 = 0;  // 计数器用作x坐标

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

    ui->gstart1_Button->setEnabled(false);
    ui->gstart2_Button->setEnabled(false);
    ui->gstart3_Button->setEnabled(false);
    ui->gstop1_Button->setEnabled(true);
    ui->gstop2_Button->setEnabled(true);
    ui->gstop3_Button->setEnabled(true);

    setupPlot1();
    setupPlot2();
    setupPlot3();

    QTimer *timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, [=]() {
        QString strData = QString::fromUtf8(receivedData);

        // 临时存储解析的数字
        QString value;
        bool isParsing = false;
        char currentType = '\0'; // 用来存储当前检测到的类型

        for (int i = 0; i < strData.length(); ++i) {
            QChar c = strData[i];

            // 如果是 f、s、t 中的任意一个类型
            if ((c == 'f' || c == 's' || c == 't') && !isParsing) {
                currentType = c.toLatin1();
                value.clear();  // 清空之前的记录
                isParsing = true;  // 开始解析
                continue;
            }

            // 如果正在解析
            if (isParsing) {
                if (c == '*') {
                    bool ok;
                    float parsedValue = value.toFloat(&ok); // 转换为浮动数值
                    if (ok) {
                        // 根据类型存储不同的数据
                        if (currentType == 'f') {
                            receivedData1.append(parsedValue);
                        } else if (currentType == 's') {
                            receivedData2.append(parsedValue);
                        } else if (currentType == 't') {
                            receivedData3.append(parsedValue);
                        }
                    }

                    // 解析完毕，重置状态
                    isParsing = false;
                    currentType = '\0';
                    continue;  // 跳过星号
                } else {
                    // 收集数值部分
                    value.append(c);
                }
            }
        }

        // 处理 f 类型的数据
        if (draw_data1 == 1 && !receivedData1.isEmpty()) {
            float yValue1 = receivedData1.at(0);
            //qDebug() << "图1: " << yValue1;
            ui->widget1->graph(0)->addData(xCount1++, yValue1);  // 添加数据
            if (xCount1 > 20) {
                ui->widget1->xAxis->setRange(xCount1 - 10, 10, Qt::AlignLeft);
            }

            ui->widget1->replot();
            receivedData1.clear();  // 清空 f 类型数据
        }

        // 处理 s 类型的数据
        if (draw_data2 == 1 && !receivedData2.isEmpty()) {
            float yValue2 = receivedData2.at(0);
            //qDebug() << "图2: " << yValue2;
            ui->widget2->graph(0)->addData(xCount2++, yValue2);  // 添加数据
            if (xCount2 > 20) {
                ui->widget2->xAxis->setRange(xCount2 - 10, 10, Qt::AlignLeft);
            }

            ui->widget2->replot();
            receivedData2.clear();  // 清空 s 类型数据
        }

        // 处理 t 类型的数据
        if (draw_data3 == 1 && !receivedData3.isEmpty()) {
            float yValue3 = receivedData3.at(0);
            //qDebug() << "图3: " << yValue3;
            ui->widget3->graph(0)->addData(xCount3++, yValue3);  // 添加数据
            if (xCount3 > 20) {
                ui->widget3->xAxis->setRange(xCount3 - 10, 10, Qt::AlignLeft);
            }

            ui->widget3->replot();
            receivedData3.clear();  // 清空 t 类型数据
        }

        // 清空接收数据
        receivedData.clear();
    });
    timer1->start(5);
}

void MainWindow::setupPlot1()
{
    // 初始化图表
    ui->widget1->clearGraphs();
    ui->widget1->addGraph();
    ui->widget1->graph(0)->rescaleAxes(true);
    ui->widget1->setBackground(QColor(240, 240, 240));

    // 设置游标
    tracer1 = new QCPItemTracer(ui->widget1);
    tracer1->setPen(QPen(Qt::red));  // 游标的颜色设置为红色
    tracer1->setBrush(QBrush(Qt::red)); // 游标填充颜色设置为红色
    tracer1->setStyle(QCPItemTracer::tsCircle); // 圆圈样式
    tracer1->setSize(5); // 游标大小

    // 游标说明
    tracerLabel1 = new QCPItemText(ui->widget1);
    tracerLabel1->setLayer("overlay");
    tracerLabel1->setPen(QPen(Qt::black)); // 游标说明颜色为黑色
    tracerLabel1->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    tracerLabel1->position->setParentAnchor(tracer1->position);
    connect(ui->widget1, &QCustomPlot::mouseMove, this, &MainWindow::myMove1);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(3);
    ui->widget1->addGraph();
    ui->widget1->graph(0)->rescaleAxes(true);
    ui->widget1->graph(0)->setPen(pen);
    ui->widget1->graph(0)->setLineStyle(QCPGraph::lsLine);  // 设置绘制连线
    ui->widget1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget1->legend->setVisible(false);  // 隐藏图例
    ui->widget1->xAxis->setVisible(true);  // 显示 x 轴
    ui->widget1->yAxis->setVisible(true);  // 显示 y 轴
    ui->widget1->xAxis->setRange(0,20);
    ui->widget1->yAxis->setRange(-100,100);

    // 设置坐标轴刻度间隔
    ui->widget1->xAxis->setTicks(5);  // 设置x轴刻度间隔为1
    ui->widget1->yAxis->setTicks(20);  // 设置y轴刻度间隔为1
}

void MainWindow::setupPlot2()
{
    // 初始化图表
    ui->widget2->clearGraphs();
    ui->widget2->addGraph();
    ui->widget2->graph(0)->rescaleAxes(true);
    ui->widget2->setBackground(QColor(240, 240, 240));

    // 设置游标
    tracer2 = new QCPItemTracer(ui->widget2);
    tracer2->setPen(QPen(Qt::red));  // 游标的颜色设置为红色
    tracer2->setBrush(QBrush(Qt::red)); // 游标填充颜色设置为红色
    tracer2->setStyle(QCPItemTracer::tsCircle); // 圆圈样式
    tracer2->setSize(5); // 游标大小

    // 游标说明
    tracerLabel2 = new QCPItemText(ui->widget2);
    tracerLabel2->setLayer("overlay");
    tracerLabel2->setPen(QPen(Qt::black)); // 游标说明颜色为黑色
    tracerLabel2->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    tracerLabel2->position->setParentAnchor(tracer2->position);
    connect(ui->widget2, &QCustomPlot::mouseMove, this, &MainWindow::myMove2);

    QPen pen1;
    pen1.setColor(Qt::red);
    pen1.setWidth(3);
    ui->widget2->addGraph();
    ui->widget2->graph(0)->rescaleAxes(true);
    ui->widget2->graph(0)->setPen(pen1);
    ui->widget2->graph(0)->setLineStyle(QCPGraph::lsLine);  // 设置绘制连线
    ui->widget2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget2->legend->setVisible(false);  // 隐藏图例
    ui->widget2->xAxis->setVisible(true);  // 显示 x 轴
    ui->widget2->yAxis->setVisible(true);  // 显示 y 轴
    ui->widget2->xAxis->setRange(0,20);
    ui->widget2->yAxis->setRange(-100,100);

    // 设置坐标轴刻度间隔
    ui->widget2->xAxis->setTicks(5);  // 设置x轴刻度间隔为1
    ui->widget2->yAxis->setTicks(20);  // 设置y轴刻度间隔为1
}

void MainWindow::setupPlot3()
{
    // 初始化图表
    ui->widget3->clearGraphs();
    ui->widget3->addGraph();
    ui->widget3->graph(0)->rescaleAxes(true);
    ui->widget3->setBackground(QColor(240, 240, 240));

    // 设置游标
    tracer3 = new QCPItemTracer(ui->widget3);
    tracer3->setPen(QPen(Qt::red));  // 游标的颜色设置为红色
    tracer3->setBrush(QBrush(Qt::red)); // 游标填充颜色设置为红色
    tracer3->setStyle(QCPItemTracer::tsCircle); // 圆圈样式
    tracer3->setSize(5); // 游标大小

    // 游标说明
    tracerLabel3 = new QCPItemText(ui->widget3);
    tracerLabel3->setLayer("overlay");
    tracerLabel3->setPen(QPen(Qt::black)); // 游标说明颜色为黑色
    tracerLabel3->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    tracerLabel3->position->setParentAnchor(tracer3->position);
    connect(ui->widget3, &QCustomPlot::mouseMove, this, &MainWindow::myMove3);

    QPen pen2;
    pen2.setColor(Qt::red);
    pen2.setWidth(3);
    ui->widget3->addGraph();
    ui->widget3->graph(0)->rescaleAxes(true);
    ui->widget3->graph(0)->setPen(pen2);
    ui->widget3->graph(0)->setLineStyle(QCPGraph::lsLine);  // 设置绘制连线
    ui->widget3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget3->legend->setVisible(false);  // 隐藏图例
    ui->widget3->xAxis->setVisible(true);  // 显示 x 轴
    ui->widget3->yAxis->setVisible(true);  // 显示 y 轴
    ui->widget3->xAxis->setRange(0,20);
    ui->widget3->yAxis->setRange(-100,100);

    // 设置坐标轴刻度间隔
    ui->widget2->xAxis->setTicks(5);  // 设置x轴刻度间隔为1
    ui->widget2->yAxis->setTicks(20);  // 设置y轴刻度间隔为1
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

    /* 设置数据位 */
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
    receivedData.append(buf);  // 将接收到的数据追加到receivedData中
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

    text.replace("，", ",");  // 替换中文逗号为英文逗号
    text.replace("。", ".");  // 替换中文句号为英文句号
    ui->send_text->setPlainText(text);

    // 确保光标在文本末尾
    QTextCursor cursor(ui->send_text->textCursor());
    cursor.movePosition(QTextCursor::End);
    ui->send_text->setTextCursor(cursor);

    QByteArray data = text.toUtf8();

    QString frameHeader = ui->headStrEdit->toPlainText(); // 帧头
    QString frameFooter = ui->tailStrEdit->toPlainText(); // 帧尾

    QByteArray frame = frameHeader.toUtf8() + data + frameFooter.toUtf8();

    Serialport->write(frame);

    //qDebug() << "发送的原始数据: " << text;

    //qDebug() << "发送的数据（字节数组形式）: " << data;

    //qDebug() << "发送的数据包（字节数组形式）: " << frame;
}

void MainWindow::myMove1(QMouseEvent *e)
{
    // 获得鼠标位置处对应的横坐标数据x
    double x1 = ui->widget1->xAxis->pixelToCoord(e->pos().x());
    tracer1->setGraph(ui->widget1->graph(0));         // 将游标和该曲线图层连接
    tracer1->setGraphKey(x1);                         // 将游标横坐标设置成刚获得的横坐标数据x
    tracer1->setInterpolating(true);                 // 游标的纵坐标可以通过曲线数据线性插值自动获得
    tracer1->updatePosition();                       // 使得刚设置游标的横纵坐标位置生效
    // 更新游标说明的内容
    double xValue1 = tracer1->position->key();
    double yValue1 = tracer1->position->value();
    tracerLabel1->setText(QString("x = %1, y = %2").arg(xValue1).arg(yValue1));
    ui->widget1->replot();                           // 重绘
}

void MainWindow::myMove2(QMouseEvent *e)
{
    // 获得鼠标位置处对应的横坐标数据x
    double x2 = ui->widget2->xAxis->pixelToCoord(e->pos().x());
    tracer2->setGraph(ui->widget2->graph(0));         // 将游标和该曲线图层连接
    tracer2->setGraphKey(x2);                         // 将游标横坐标设置成刚获得的横坐标数据x
    tracer2->setInterpolating(true);                 // 游标的纵坐标可以通过曲线数据线性插值自动获得
    tracer2->updatePosition();                       // 使得刚设置游标的横纵坐标位置生效
    // 更新游标说明的内容
    double xValue2 = tracer2->position->key();
    double yValue2 = tracer2->position->value();
    tracerLabel2->setText(QString("x = %1, y = %2").arg(xValue2).arg(yValue2));
    ui->widget2->replot();                           // 重绘
}

void MainWindow::myMove3(QMouseEvent *e)
{
    // 获得鼠标位置处对应的横坐标数据x
    double x3 = ui->widget3->xAxis->pixelToCoord(e->pos().x());
    tracer3->setGraph(ui->widget3->graph(0));         // 将游标和该曲线图层连接
    tracer3->setGraphKey(x3);                         // 将游标横坐标设置成刚获得的横坐标数据x
    tracer3->setInterpolating(true);                 // 游标的纵坐标可以通过曲线数据线性插值自动获得
    tracer3->updatePosition();                       // 使得刚设置游标的横纵坐标位置生效
    // 更新游标说明的内容
    double xValue3 = tracer3->position->key();
    double yValue3 = tracer3->position->value();
    tracerLabel3->setText(QString("x = %1, y = %2").arg(xValue3).arg(yValue3));
    ui->widget3->replot();                           // 重绘
}

void MainWindow::on_gstart1_Button_clicked()
{
    // 启动定时器，开始绘图
    draw_data1 = 1;

    ui->gstop1_Button->setEnabled(true);
    ui->gstart1_Button->setEnabled(false);
}

void MainWindow::on_gstop1_Button_clicked()
{
    // 停止定时器，停止绘图
    draw_data1 = 0;

    ui->gstart1_Button->setEnabled(true);  // 启用开始按钮
    ui->gstop1_Button->setEnabled(false);  // 禁用停止按钮
}

void MainWindow::on_gclear1_Button_clicked()
{
    // 清除现有图表数据
    xCount1 = 0;
    ui->widget1->clearGraphs();  // 清除图表
    ui->widget1->clearPlottables();
    ui->widget1->clearItems();      // 清除所有项目（如文本、游标等）
    // 重新添加一个空图表，避免后续访问错误
    ui->widget1->addGraph();  // 添加一个空图表
    setupPlot1();
    ui->widget1->replot();
}

void MainWindow::on_gclear2_Button_clicked()
{
    // 清除现有图表数据
    xCount2 = 0;
    ui->widget2->clearGraphs();  // 清除图表
    ui->widget2->clearPlottables();
    ui->widget2->clearItems();      // 清除所有项目（如文本、游标等）
    // 重新添加一个空图表，避免后续访问错误
    ui->widget2->addGraph();  // 添加一个空图表
    setupPlot2();
    ui->widget2->replot();
}

void MainWindow::on_gstart2_Button_clicked()
{
    // 启动定时器，开始绘图
    draw_data2 = 1;

    ui->gstop2_Button->setEnabled(true);
    ui->gstart2_Button->setEnabled(false);
}

void MainWindow::on_gstop2_Button_clicked()
{
    // 停止定时器，停止绘图
    draw_data2 = 0;

    ui->gstart2_Button->setEnabled(true);  // 启用开始按钮
    ui->gstop2_Button->setEnabled(false);  // 禁用停止按钮
}

void MainWindow::on_gstart3_Button_clicked()
{
    // 启动定时器，开始绘图
    draw_data3 = 1;

    ui->gstop3_Button->setEnabled(true);
    ui->gstart3_Button->setEnabled(false);
}

void MainWindow::on_gstop3_Button_clicked()
{
    // 停止定时器，停止绘图
    draw_data3 = 0;

    ui->gstart3_Button->setEnabled(true);  // 启用开始按钮
    ui->gstop3_Button->setEnabled(false);  // 禁用停止按钮
}

void MainWindow::on_gclear3_Button_clicked()
{
    // 清除现有图表数据
    xCount3 = 0;
    ui->widget3->clearGraphs();  // 清除图表
    ui->widget3->clearPlottables();
    ui->widget3->clearItems();      // 清除所有项目（如文本、游标等）
    // 重新添加一个空图表，避免后续访问错误
    ui->widget3->addGraph();  // 添加一个空图表
    setupPlot3();
    ui->widget3->replot();
}
