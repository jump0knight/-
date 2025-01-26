/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_9;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *receive_text;
    QHBoxLayout *horizontalLayout;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *receive_cleanButton;
    QLabel *label_2;
    QTextEdit *send_text;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QTextEdit *headStrEdit;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_14;
    QTextEdit *tailStrEdit;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sendButton;
    QPushButton *send_cleanButton;
    QVBoxLayout *verticalLayout_2;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBox_port;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QComboBox *comboBox_boadrate;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_open_serial;
    QPushButton *btn_close_serial;
    QWidget *tab_10;
    QCustomPlot *widget1;
    QCustomPlot *widget2;
    QCustomPlot *widget3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_5;
    QPushButton *gstart1_Button;
    QSpacerItem *verticalSpacer_4;
    QPushButton *gstop1_Button;
    QSpacerItem *verticalSpacer_3;
    QPushButton *gclear1_Button;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_9;
    QPushButton *gstart2_Button;
    QSpacerItem *verticalSpacer_8;
    QPushButton *gstop2_Button;
    QSpacerItem *verticalSpacer_7;
    QPushButton *gclear2_Button;
    QSpacerItem *verticalSpacer_6;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_12;
    QPushButton *gstart3_Button;
    QPushButton *gstop3_Button;
    QSpacerItem *verticalSpacer_13;
    QPushButton *gclear3_Button;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_10;
    QWidget *tab_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(825, 614);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 0, 781, 551));
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        verticalLayoutWidget_3 = new QWidget(tab_9);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(0, 0, 591, 521));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        receive_text = new QTextEdit(verticalLayoutWidget_3);
        receive_text->setObjectName(QString::fromUtf8("receive_text"));
        receive_text->setEnabled(true);

        verticalLayout->addWidget(receive_text);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        line_2 = new QFrame(verticalLayoutWidget_3);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        receive_cleanButton = new QPushButton(verticalLayoutWidget_3);
        receive_cleanButton->setObjectName(QString::fromUtf8("receive_cleanButton"));
        receive_cleanButton->setFont(font);

        horizontalLayout->addWidget(receive_cleanButton);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        send_text = new QTextEdit(verticalLayoutWidget_3);
        send_text->setObjectName(QString::fromUtf8("send_text"));

        verticalLayout->addWidget(send_text);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(-1, 0, -1, -1);
        label_13 = new QLabel(verticalLayoutWidget_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMaximumSize(QSize(40, 30));
        label_13->setBaseSize(QSize(4, 6));

        horizontalLayout_15->addWidget(label_13);

        headStrEdit = new QTextEdit(verticalLayoutWidget_3);
        headStrEdit->setObjectName(QString::fromUtf8("headStrEdit"));
        headStrEdit->setMaximumSize(QSize(80, 30));

        horizontalLayout_15->addWidget(headStrEdit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_7);

        label_14 = new QLabel(verticalLayoutWidget_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(40, 30));

        horizontalLayout_15->addWidget(label_14);

        tailStrEdit = new QTextEdit(verticalLayoutWidget_3);
        tailStrEdit->setObjectName(QString::fromUtf8("tailStrEdit"));
        tailStrEdit->setMaximumSize(QSize(80, 30));

        horizontalLayout_15->addWidget(tailStrEdit);


        horizontalLayout_2->addLayout(horizontalLayout_15);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        sendButton = new QPushButton(verticalLayoutWidget_3);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setFont(font);

        horizontalLayout_2->addWidget(sendButton);

        send_cleanButton = new QPushButton(verticalLayoutWidget_3);
        send_cleanButton->setObjectName(QString::fromUtf8("send_cleanButton"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        send_cleanButton->setFont(font1);

        horizontalLayout_2->addWidget(send_cleanButton);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayoutWidget_4 = new QWidget(tab_9);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(610, 20, 151, 491));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(verticalLayoutWidget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        comboBox_port = new QComboBox(verticalLayoutWidget_4);
        comboBox_port->setObjectName(QString::fromUtf8("comboBox_port"));

        horizontalLayout_4->addWidget(comboBox_port);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(verticalLayoutWidget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        horizontalLayout_6->addWidget(label_5);

        comboBox_boadrate = new QComboBox(verticalLayoutWidget_4);
        comboBox_boadrate->addItem(QString());
        comboBox_boadrate->addItem(QString());
        comboBox_boadrate->addItem(QString());
        comboBox_boadrate->addItem(QString());
        comboBox_boadrate->setObjectName(QString::fromUtf8("comboBox_boadrate"));

        horizontalLayout_6->addWidget(comboBox_boadrate);


        verticalLayout_4->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        btn_open_serial = new QPushButton(verticalLayoutWidget_4);
        btn_open_serial->setObjectName(QString::fromUtf8("btn_open_serial"));
        btn_open_serial->setFont(font);

        verticalLayout_4->addWidget(btn_open_serial);

        btn_close_serial = new QPushButton(verticalLayoutWidget_4);
        btn_close_serial->setObjectName(QString::fromUtf8("btn_close_serial"));
        btn_close_serial->setFont(font);

        verticalLayout_4->addWidget(btn_close_serial);

        tabWidget->addTab(tab_9, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QString::fromUtf8("tab_10"));
        widget1 = new QCustomPlot(tab_10);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(30, 10, 591, 161));
        widget2 = new QCustomPlot(tab_10);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(30, 180, 591, 161));
        widget3 = new QCustomPlot(tab_10);
        widget3->setObjectName(QString::fromUtf8("widget3"));
        widget3->setGeometry(QRect(30, 350, 591, 161));
        verticalLayoutWidget = new QWidget(tab_10);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(650, 80, 112, 98));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        gstart1_Button = new QPushButton(verticalLayoutWidget);
        gstart1_Button->setObjectName(QString::fromUtf8("gstart1_Button"));

        verticalLayout_5->addWidget(gstart1_Button);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        gstop1_Button = new QPushButton(verticalLayoutWidget);
        gstop1_Button->setObjectName(QString::fromUtf8("gstop1_Button"));

        verticalLayout_5->addWidget(gstop1_Button);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        gclear1_Button = new QPushButton(verticalLayoutWidget);
        gclear1_Button->setObjectName(QString::fromUtf8("gclear1_Button"));

        verticalLayout_5->addWidget(gclear1_Button);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        verticalLayoutWidget_2 = new QWidget(tab_10);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(650, 250, 112, 98));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_9);

        gstart2_Button = new QPushButton(verticalLayoutWidget_2);
        gstart2_Button->setObjectName(QString::fromUtf8("gstart2_Button"));

        verticalLayout_6->addWidget(gstart2_Button);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        gstop2_Button = new QPushButton(verticalLayoutWidget_2);
        gstop2_Button->setObjectName(QString::fromUtf8("gstop2_Button"));

        verticalLayout_6->addWidget(gstop2_Button);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_7);

        gclear2_Button = new QPushButton(verticalLayoutWidget_2);
        gclear2_Button->setObjectName(QString::fromUtf8("gclear2_Button"));

        verticalLayout_6->addWidget(gclear2_Button);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_6);

        verticalLayoutWidget_5 = new QWidget(tab_10);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(650, 420, 112, 98));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_12);

        gstart3_Button = new QPushButton(verticalLayoutWidget_5);
        gstart3_Button->setObjectName(QString::fromUtf8("gstart3_Button"));

        verticalLayout_7->addWidget(gstart3_Button);

        gstop3_Button = new QPushButton(verticalLayoutWidget_5);
        gstop3_Button->setObjectName(QString::fromUtf8("gstop3_Button"));

        verticalLayout_7->addWidget(gstop3_Button);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_13);

        gclear3_Button = new QPushButton(verticalLayoutWidget_5);
        gclear3_Button->setObjectName(QString::fromUtf8("gclear3_Button"));

        verticalLayout_7->addWidget(gclear3_Button);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_11);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_10);

        tabWidget->addTab(tab_10, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName(QString::fromUtf8("tab_11"));
        tabWidget->addTab(tab_11, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 825, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\216\245\346\224\266\345\214\272", nullptr));
        receive_cleanButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\216\245\346\224\266\345\214\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\214\272", nullptr));
        send_text->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\345\270\247\345\244\264", nullptr));
        headStrEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">$</p></body></html>", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\345\270\247\345\260\276", nullptr));
        tailStrEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">*</p></body></html>", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        send_cleanButton->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\217\221\351\200\201\345\214\272", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        comboBox_boadrate->setItemText(0, QCoreApplication::translate("MainWindow", "4800", nullptr));
        comboBox_boadrate->setItemText(1, QCoreApplication::translate("MainWindow", "9600", nullptr));
        comboBox_boadrate->setItemText(2, QCoreApplication::translate("MainWindow", "38400", nullptr));
        comboBox_boadrate->setItemText(3, QCoreApplication::translate("MainWindow", "115200", nullptr));

        btn_open_serial->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        btn_close_serial->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_9), QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\250\241\345\274\217", nullptr));
        gstart1_Button->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        gstop1_Button->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        gclear1_Button->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244", nullptr));
        gstart2_Button->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        gstop2_Button->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        gclear2_Button->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244", nullptr));
        gstart3_Button->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        gstop3_Button->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        gclear3_Button->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_10), QCoreApplication::translate("MainWindow", "\346\263\242\345\275\242\345\233\276\346\250\241\345\274\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_11), QCoreApplication::translate("MainWindow", "\345\247\277\346\200\201\350\247\222\350\257\273\345\217\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
