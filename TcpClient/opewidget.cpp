#include "opewidget.h"
#include <QListWidgetItem>
#include <QPainterPath>
#include <QPainter>
#include <QFileDialog>
OpeWidget::OpeWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(1000,500);

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
    m_profile->setFixedSize(40,40);
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
    m_profile->installEventFilter(this);

    QHBoxLayout *topVBL = new QHBoxLayout;
    //topVBL->setFixedWidth(175,100);
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

    setHand();
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

bool OpeWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj) == m_profile && event->type() == QEvent::MouseButtonRelease)
    {
        qDebug() << "点击了头像";
        //模态QFileDialog使用静态函数创建，根据第三个参数选择路径打开对话框，第四个参数寻找该路径下与之相匹配的文件
        QString filePath = QFileDialog::getOpenFileName(this,tr("Open Image"),"../TcpClient",tr("Image Files (*.png *.jpg *.bmp)"));
        if(filePath == ""){
            return true;
        }
        qDebug() << filePath;
        int index = filePath.lastIndexOf("/");
        QString fileName = filePath.mid(index+1,filePath.size()-index);
        qDebug() << fileName;
        QString dstPath = QCoreApplication::applicationDirPath();

        dstPath.chop(dstPath.size()-dstPath.lastIndexOf("/"));
        dstPath.chop(dstPath.size()-dstPath.lastIndexOf("/"));
        qDebug() << "dstPath：" <<dstPath;
        dstPath = dstPath + "/TcpClient/Img/" + fileName;
        filePath.replace("\\","/");
        dstPath.replace("\\","/");
        bool ret = QFile::copy(filePath,dstPath);
        qDebug() << "文件复制：" << ret;

        //写头像文件信息
        QFile file("../TcpClient/Img.txt");
        bool l = file.open(QIODevice::WriteOnly | QIODevice::Text);
        if(l == true)
        {
            qDebug() << "打开文件成成功";
            file.write(dstPath.toStdString().c_str());
            //file.write("\n");
        }
        file.close();

        QPixmap tmpPix;
        tmpPix.load(dstPath);
        //图片缩放
        //Qt::KeepAspectRatio  保持图片比例，缩放到size内最大矩形
        tmpPix.scaled(m_profile->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        m_profile->setScaledContents(true);
        m_profile->setPixmap(tmpPix);
        return true;
    }
    else
    {
        return false;
    }
}

void OpeWidget::setHand()
{
    qDebug() << "设置头像";
    QFile file("../TcpClient/Img.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "读取文件失败";
        return;
    }

    QByteArray line = file.readLine();
    QString path = line.toStdString().c_str();
    path = path.trimmed();//去掉换行符
    QPixmap tmpPix;
    tmpPix.load(path);
    tmpPix.scaled(m_profile->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    m_profile->setScaledContents(true);
    m_profile->setPixmap(tmpPix);
    file.close();
}


//客户端选择一个头像文件
//将该文件复制一份并在txt文件中留下记录
//客户端登录的时候，读取txt文件，并加载头像

