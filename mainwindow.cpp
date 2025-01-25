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

bool draw_data = 0;
bool data_get = 0;
int xCount = 0;  // 计数器用作x坐标

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

    ui->gstop1_Button->setEnabled(false);
    ui->gstop2_Button->setEnabled(false);
    ui->gstop3_Button->setEnabled(false);

    setupPlot();

    QTimer *timer1 = new QTimer(this);
    connect(timer1,&QTimer::timeout,this,[=](){
        if(draw_data == 1){
            QString strData = QString::fromUtf8(receivedData);

            // 假设接收到的数据格式是 f11* 这样可以解析出 11
            QRegExp regex("f(-?\\d*\\.\\d+|\\d+\\.\\d*|\\d+)*\\*");
                    if (regex.indexIn(strData) != -1) {
                        QString value = regex.cap(1);  // 获取括号中的数字部分
                        bool ok;
                        float yValue = value.toFloat(&ok);
                        if (ok) {
                            // 获取图表的最新x坐标并添加数据
                            ui->widget1->graph(0)->addData(xCount++, yValue);  // 添加数据

                            // 控制图表的 x 轴在添加一定数据点后才更新
                            if (xCount > 20) {
                                // 缓慢移动：逐渐更新x轴范围
                                ui->widget1->xAxis->setRange(xCount-10, 10, Qt::AlignLeft);
                            }

                            // 添加数据到图表并重绘
                            addDataToGraph(xCount, yValue);
                            ui->widget1->replot();  // 重新绘制图表
                        }
                    }
        }
        receivedData.clear();
        });
    timer1->start(5);
}

void MainWindow::setupPlot()
{
    // 初始化图表
    ui->widget1->clearGraphs();
    ui->widget1->addGraph();
    ui->widget1->graph(0)->rescaleAxes(true);
    ui->widget1->setBackground(QColor(240, 240, 240));

    // 设置游标
    tracer = new QCPItemTracer(ui->widget1);
    tracer->setPen(QPen(Qt::red));  // 游标的颜色设置为红色
    tracer->setBrush(QBrush(Qt::red)); // 游标填充颜色设置为红色
    tracer->setStyle(QCPItemTracer::tsCircle); // 圆圈样式
    tracer->setSize(5); // 游标大小

    // 游标说明
    tracerLabel = new QCPItemText(ui->widget1);
    tracerLabel->setLayer("overlay");
    tracerLabel->setPen(QPen(Qt::black)); // 游标说明颜色为黑色
    tracerLabel->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
    tracerLabel->position->setParentAnchor(tracer->position);
    connect(ui->widget1, &QCustomPlot::mouseMove, this, &MainWindow::myMove);

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

void MainWindow::myMove(QMouseEvent *e)
{
    // 获得鼠标位置处对应的横坐标数据x
    double x = ui->widget1->xAxis->pixelToCoord(e->pos().x());
    tracer->setGraph(ui->widget1->graph(0));         // 将游标和该曲线图层连接
    tracer->setGraphKey(x);                         // 将游标横坐标设置成刚获得的横坐标数据x
    tracer->setInterpolating(true);                 // 游标的纵坐标可以通过曲线数据线性插值自动获得
    tracer->updatePosition();                       // 使得刚设置游标的横纵坐标位置生效
    // 更新游标说明的内容
    double xValue = tracer->position->key();
    double yValue = tracer->position->value();
    tracerLabel->setText(QString("x = %1, y = %2").arg(xValue).arg(yValue));
    ui->widget1->replot();                           // 重绘
}

void MainWindow::addDataToGraph(double x, double y)
{
    // 添加数据点到图表
    ui->widget1->graph(0)->addData(x, y);

    // 获取当前图表的 Y 轴范围
    double currentMinY = ui->widget1->yAxis->range().lower;
    double currentMaxY = ui->widget1->yAxis->range().upper;

    // 检查当前数据点是否超出 Y 轴范围
    double newMinY = std::min(currentMinY, y);
    double newMaxY = std::max(currentMaxY, y);

    // 如果数据超出范围，更新 Y 轴的范围
    if (newMinY != currentMinY || newMaxY != currentMaxY) {
        ui->widget1->yAxis->setRange(newMinY - 50, newMaxY + 50); // 增加一点额外的空白区间
        ui->widget1->replot();  // 更新图表
    }
}

void MainWindow::on_gstart1_Button_clicked()
{
    // 启动定时器，开始绘图
    draw_data = 1;

    ui->gstop1_Button->setEnabled(true);
    ui->gstart1_Button->setEnabled(false);
}

void MainWindow::on_gstop1_Button_clicked()
{
    // 停止定时器，停止绘图
    draw_data = 0;

    ui->gstart1_Button->setEnabled(true);  // 启用开始按钮
    ui->gstop1_Button->setEnabled(false);  // 禁用停止按钮
}

void MainWindow::on_gclear1_Button_clicked()
{
    if(draw_data==0)
    {
        ui->gstart1_Button->setEnabled(true);  // 启用开始按钮
        ui->gstop1_Button->setEnabled(false);  // 禁用停止按钮
    }
    else
    {
        ui->gstop1_Button->setEnabled(true);
        ui->gstart1_Button->setEnabled(false);
    }
    // 清除现有图表数据
    xCount = 0;
    ui->widget1->clearGraphs();  // 清除图表
    ui->widget1->clearPlottables();
    ui->widget1->clearItems();      // 清除所有项目（如文本、游标等）
    // 重新添加一个空图表，避免后续访问错误
    ui->widget1->addGraph();  // 添加一个空图表
    setupPlot();
    ui->widget1->replot();
}
