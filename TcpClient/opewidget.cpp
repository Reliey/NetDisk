#include "opewidget.h"
#include <QListWidgetItem>
#include <QPainterPath>
#include <QPainter>
OpeWidget::OpeWidget(QWidget *parent) : QWidget(parent)
{
    m_pListW = new QListWidget(this);
//    m_pListW->addItem("好友");
//    m_pListW->addItem("图书");

    QListWidgetItem *item = new QListWidgetItem;
    QPixmap icon(":/opewidget/friend.png");
    icon = icon.scaled(100,100);
    QIcon qicon(icon);
    item->setIcon(qicon);
    item->setText("好友");
    m_pListW->addItem(item);

    QListWidgetItem *item2 = new QListWidgetItem;
    QPixmap icon2(":/opewidget/file.png");
    icon2 = icon2.scaled(100,100);
    QIcon qicon2(icon2);
    item2->setIcon(qicon2);
    item2->setText("文件");
    m_pListW->addItem(item2);

    m_vframe = new QFrame;
    m_vframe->setFrameShape(QFrame::VLine); //设置垂直线
    m_vframe->setFrameShadow(QFrame::Plain);
    m_vframe->setStyleSheet("width:1px;color:rgba(30,32,40,1)");
    m_hframe = new QFrame;
    m_hframe->setFrameShape(QFrame::HLine); //设置水平线
    m_hframe->setFrameShadow(QFrame::Plain);
    m_hframe->setStyleSheet("width:1px;color:rgba(30,32,40,1)");

    m_pFriend = new Friend;
    m_pBook = new Book;
    m_profile = new QLabel;
    QString name = TcpClient::getInstance().loginName();
    m_name = new QLabel(name);


    QPixmap pixmapa(":/opewidget/friend.png");
    QPixmap pixmap(40,40);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(1,1,40,40);    //绘制椭圆
    painter.setClipPath(path);
    painter.drawPixmap(1,1,40,40, pixmapa);
    m_profile->setPixmap(pixmap);

    QHBoxLayout *topVBL = new QHBoxLayout;
    topVBL->addWidget(m_profile);
    topVBL->addWidget(m_name);
    topVBL->setAlignment(Qt::AlignCenter);

    m_pSW = new QStackedWidget;
    m_pSW->addWidget(m_pFriend);
    m_pSW->addWidget(m_pBook);

    QVBoxLayout *pLeftVBL = new QVBoxLayout;
    pLeftVBL->addLayout(topVBL);
    pLeftVBL->addWidget(m_hframe);
    pLeftVBL->addWidget(m_pListW);
    pLeftVBL->setSpacing(0);

    QHBoxLayout *pMain = new QHBoxLayout;
    pMain->addLayout(pLeftVBL);
    pMain->addWidget(m_vframe);
    pMain->addWidget(m_pSW);
    pMain->setSpacing(0);

    setLayout(pMain);

    setWindowIcon(QIcon(":/map/netdisk.png"));
    setWindowTitle("网盘");

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor("#ffffff"));
    this->setPalette(palette);

//    m_pListW->setStyleSheet("background-color: rgb(245,245,246)");
    m_pListW->setFixedWidth(175);

    m_pListW->setIconSize(QSize(25, 25));
    m_pListW->setFocusPolicy(Qt::NoFocus);  //这样可禁用tab键和上下方向键并且除去复选框
//    m_pListW->setFixedHeight(320);
    m_pListW->setFont(QFont("Microsoft YaHei", 15, QFont::DemiBold));
    m_pListW->setStyleSheet(
                //"*{outline:0px;}"  //除去复选框
                "QListWidget{background:rgb(245, 245, 247); border:0px; margin:0px 0px 0px 0px;}"
                "QListWidget::Item{height:50px; border:0px; padding-left:14px; color:rgba(200, 40, 40, 255);border-radius: 7px;}"
                "QListWidget::Item:hover{background-color:rgba(132,133,141,16); padding-left:14px;}"
                "QListWidget::Item:selected{color:rgba(40, 40, 200, 255); padding-left:15px;}"
                );
    connect(m_pListW,SIGNAL(currentRowChanged(int)),m_pSW,SLOT(setCurrentIndex(int)));

}

OpeWidget &OpeWidget::getInstance()
{
    static OpeWidget instance;
    return instance;
}

Friend *OpeWidget::getFriend()
{
    return m_pFriend;
}

Book *OpeWidget::getBook()
{
    return m_pBook;
}


