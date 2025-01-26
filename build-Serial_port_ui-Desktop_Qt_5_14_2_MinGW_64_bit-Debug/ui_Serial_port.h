/********************************************************************************
** Form generated from reading UI file 'Serial_port.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIAL_PORT_H
#define UI_SERIAL_PORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *receive_text;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *receive_cleanButton;
    QLabel *label_2;
    QTextEdit *send_text;
    QHBoxLayout *horizontalLayout_2;
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
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menuV;
    QMenu *menu1_0;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(20, 20, 591, 521));
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

        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(630, 40, 151, 491));
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

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuV = new QMenu(menubar);
        menuV->setObjectName(QString::fromUtf8("menuV"));
        menu1_0 = new QMenu(menubar);
        menu1_0->setObjectName(QString::fromUtf8("menu1_0"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menuV->menuAction());
        menubar->addAction(menu1_0->menuAction());

        retranslateUi(MainWindow);

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
        menu->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\344\270\212\344\275\215\346\234\272", nullptr));
        menuV->setTitle(QCoreApplication::translate("MainWindow", "V", nullptr));
        menu1_0->setTitle(QCoreApplication::translate("MainWindow", "1.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIAL_PORT_H
