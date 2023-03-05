/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QLabel *hand;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *icon;
    QLabel *text;
    QSpacerItem *horizontalSpacer;
    QPushButton *min;
    QPushButton *close;
    QLabel *back;
    QWidget *widget_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *name_lab;
    QLineEdit *name_le;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pwd_lab;
    QLineEdit *pwd_le;
    QPushButton *login_pb;
    QPushButton *cancel_pb;
    QPushButton *regist_pb;

    void setupUi(QWidget *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName(QStringLiteral("TcpClient"));
        TcpClient->resize(640, 445);
        TcpClient->setMinimumSize(QSize(640, 445));
        TcpClient->setMaximumSize(QSize(640, 446));
        TcpClient->setStyleSheet(QStringLiteral(""));
        hand = new QLabel(TcpClient);
        hand->setObjectName(QStringLiteral("hand"));
        hand->setGeometry(QRect(290, 120, 70, 70));
        hand->setMinimumSize(QSize(70, 70));
        hand->setMaximumSize(QSize(70, 70));
        hand->setStyleSheet(QLatin1String("border-image: url(:/map/netdisk.png);\n"
"border-width:0px;\n"
"border-radius:33px;\n"
"border-style:solid;\n"
"border-color: rgb(255, 255, 255);"));
        widget = new QWidget(TcpClient);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 641, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        icon = new QLabel(widget);
        icon->setObjectName(QStringLiteral("icon"));
        icon->setMinimumSize(QSize(60, 50));
        icon->setMaximumSize(QSize(60, 50));
        QFont font;
        font.setPointSize(12);
        icon->setFont(font);
        icon->setScaledContents(false);

        horizontalLayout->addWidget(icon);

        text = new QLabel(widget);
        text->setObjectName(QStringLiteral("text"));
        text->setMinimumSize(QSize(60, 50));
        text->setMaximumSize(QSize(60, 50));
        QFont font1;
        font1.setPointSize(13);
        text->setFont(font1);

        horizontalLayout->addWidget(text);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        min = new QPushButton(widget);
        min->setObjectName(QStringLiteral("min"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/map/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        min->setIcon(icon1);
        min->setFlat(true);

        horizontalLayout->addWidget(min);

        close = new QPushButton(widget);
        close->setObjectName(QStringLiteral("close"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/map/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        close->setIcon(icon2);
        close->setFlat(true);

        horizontalLayout->addWidget(close);

        back = new QLabel(TcpClient);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(0, 0, 640, 190));
        back->setMinimumSize(QSize(640, 190));
        back->setMaximumSize(QSize(640, 190));
        back->setStyleSheet(QStringLiteral(""));
        widget_3 = new QWidget(TcpClient);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(0, 190, 641, 271));
        widget_3->setMinimumSize(QSize(641, 271));
        widget_3->setMaximumSize(QSize(641, 271));
        widget_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(70, 0, 454, 121));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        name_lab = new QLabel(widget_2);
        name_lab->setObjectName(QStringLiteral("name_lab"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(name_lab->sizePolicy().hasHeightForWidth());
        name_lab->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QStringLiteral("AcadEref"));
        font2.setPointSize(20);
        name_lab->setFont(font2);

        horizontalLayout_2->addWidget(name_lab);

        name_le = new QLineEdit(widget_2);
        name_le->setObjectName(QStringLiteral("name_le"));
        sizePolicy.setHeightForWidth(name_le->sizePolicy().hasHeightForWidth());
        name_le->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(20);
        name_le->setFont(font3);

        horizontalLayout_2->addWidget(name_le);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pwd_lab = new QLabel(widget_2);
        pwd_lab->setObjectName(QStringLiteral("pwd_lab"));
        sizePolicy.setHeightForWidth(pwd_lab->sizePolicy().hasHeightForWidth());
        pwd_lab->setSizePolicy(sizePolicy);
        pwd_lab->setFont(font2);

        horizontalLayout_3->addWidget(pwd_lab);

        pwd_le = new QLineEdit(widget_2);
        pwd_le->setObjectName(QStringLiteral("pwd_le"));
        sizePolicy.setHeightForWidth(pwd_le->sizePolicy().hasHeightForWidth());
        pwd_le->setSizePolicy(sizePolicy);
        pwd_le->setFont(font3);
        pwd_le->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(pwd_le);


        verticalLayout->addLayout(horizontalLayout_3);

        login_pb = new QPushButton(widget_3);
        login_pb->setObjectName(QStringLiteral("login_pb"));
        login_pb->setGeometry(QRect(220, 130, 291, 47));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(24);
        login_pb->setFont(font4);
        login_pb->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	color:black;\n"
"	background-color: rgb(85, 170, 255);\n"
"	border: none;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(228 , 240 , 250);\n"
"	border: 1px solid rgb(15 , 150 , 255);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(204 , 228 , 247);\n"
"	border: 1px solid rgb(1 , 84 , 153);\n"
"	padding-left:3px;\n"
"	padding-top:3px;\n"
"}\n"
""));
        cancel_pb = new QPushButton(widget_3);
        cancel_pb->setObjectName(QStringLiteral("cancel_pb"));
        cancel_pb->setGeometry(QRect(580, 220, 56, 29));
        sizePolicy.setHeightForWidth(cancel_pb->sizePolicy().hasHeightForWidth());
        cancel_pb->setSizePolicy(sizePolicy);
        QFont font5;
        font5.setFamily(QStringLiteral("AcadEref"));
        font5.setPointSize(16);
        cancel_pb->setFont(font5);
        cancel_pb->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	color:black;\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: none;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(228 , 240 , 250);\n"
"	border: 1px solid rgb(15 , 150 , 255);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(204 , 228 , 247);\n"
"	border: 1px solid rgb(1 , 84 , 153);\n"
"	padding-left:3px;\n"
"	padding-top:3px;\n"
"}\n"
""));
        cancel_pb->setFlat(true);
        regist_pb = new QPushButton(widget_3);
        regist_pb->setObjectName(QStringLiteral("regist_pb"));
        regist_pb->setGeometry(QRect(10, 220, 56, 29));
        sizePolicy.setHeightForWidth(regist_pb->sizePolicy().hasHeightForWidth());
        regist_pb->setSizePolicy(sizePolicy);
        regist_pb->setFont(font5);
        regist_pb->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	color:black;\n"
"	background-color: rgb(255, 255, 255);\n"
"	border: none;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(228 , 240 , 250);\n"
"	border: 1px solid rgb(15 , 150 , 255);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(204 , 228 , 247);\n"
"	border: 1px solid rgb(1 , 84 , 153);\n"
"	padding-left:3px;\n"
"	padding-top:3px;\n"
"}\n"
""));
        regist_pb->setFlat(true);
        back->raise();
        widget->raise();
        hand->raise();
        widget_3->raise();

        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QWidget *TcpClient)
    {
        TcpClient->setWindowTitle(QApplication::translate("TcpClient", "TcpClient", Q_NULLPTR));
        hand->setText(QString());
        icon->setText(QApplication::translate("TcpClient", "\345\233\276\346\240\207", Q_NULLPTR));
        text->setText(QApplication::translate("TcpClient", "\347\275\221\347\233\230", Q_NULLPTR));
        min->setText(QString());
        close->setText(QString());
        back->setText(QApplication::translate("TcpClient", "\350\203\214\346\231\257", Q_NULLPTR));
        name_lab->setText(QApplication::translate("TcpClient", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        pwd_lab->setText(QApplication::translate("TcpClient", "\345\257\206  \347\240\201\357\274\232", Q_NULLPTR));
        login_pb->setText(QApplication::translate("TcpClient", "\347\231\273\345\275\225", Q_NULLPTR));
        cancel_pb->setText(QApplication::translate("TcpClient", "\346\263\250\351\224\200", Q_NULLPTR));
        regist_pb->setText(QApplication::translate("TcpClient", "\346\263\250\345\206\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
