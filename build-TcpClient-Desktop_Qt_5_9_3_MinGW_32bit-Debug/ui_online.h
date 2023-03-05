/********************************************************************************
** Form generated from reading UI file 'online.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINE_H
#define UI_ONLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Online
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *online_lw;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *addFriend_pb;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Online)
    {
        if (Online->objectName().isEmpty())
            Online->setObjectName(QStringLiteral("Online"));
        Online->resize(574, 421);
        verticalLayout_2 = new QVBoxLayout(Online);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        online_lw = new QListWidget(Online);
        new QListWidgetItem(online_lw);
        online_lw->setObjectName(QStringLiteral("online_lw"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(online_lw->sizePolicy().hasHeightForWidth());
        online_lw->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(16);
        online_lw->setFont(font);

        horizontalLayout->addWidget(online_lw);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        addFriend_pb = new QPushButton(Online);
        addFriend_pb->setObjectName(QStringLiteral("addFriend_pb"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(24);
        font1.setBold(true);
        font1.setWeight(75);
        addFriend_pb->setFont(font1);
        addFriend_pb->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	color:black;\n"
"	background-color:rgb(238 , 238 , 238);\n"
"	border: 1px solid rgb(183 , 183 , 183);\n"
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

        verticalLayout->addWidget(addFriend_pb);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Online);

        QMetaObject::connectSlotsByName(Online);
    } // setupUi

    void retranslateUi(QWidget *Online)
    {
        Online->setWindowTitle(QApplication::translate("Online", "Form", Q_NULLPTR));

        const bool __sortingEnabled = online_lw->isSortingEnabled();
        online_lw->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = online_lw->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Online", "1111", Q_NULLPTR));
        online_lw->setSortingEnabled(__sortingEnabled);

        addFriend_pb->setText(QApplication::translate("Online", "\345\212\240\345\245\275\345\217\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Online: public Ui_Online {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINE_H
