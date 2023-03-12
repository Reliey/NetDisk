#include "friend.h"
#include "tcpclient.h"
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QLabel>
#include <QtWidgets/QApplication>

Friend::Friend(QWidget *parent) : QWidget(parent)
{
    QFile file(":/myQSS.qss");
    file.open(QIODevice::ReadOnly);
    qApp->setStyleSheet(file.readAll());
    file.close();

    m_pShowMsgTE = new QTextEdit;
    m_pFriendListWidget = new QListWidget;
    m_pInputMsgLE = new QLineEdit;

    m_pDelFriendPB = new QPushButton;
    m_pFlushFriendPB = new QPushButton;
    m_pShowOnlineUsrPB = new QPushButton("显示在线用户");
    m_pSearchUsrPB = new QPushButton;
    m_pMsgSendPB = new QPushButton("信息发送");
    m_pPrivateChatPB = new QPushButton("私聊");

    //消息显示只读
    m_pShowMsgTE->setReadOnly(true);

    m_pFlushFriendPB->setObjectName("m_pFlushFriendPB");
    m_pDelFriendPB->setObjectName("m_pDelFriendPB");
    m_pSearchUsrPB->setObjectName("m_pSearchUsrPB");
    m_pMsgSendPB->setObjectName("m_pMsgSendPB");
    m_pShowOnlineUsrPB->setObjectName("m_pShowOnlineUsrPB");
    m_pPrivateChatPB->setObjectName("m_pPrivateChatPB");

    m_pSearchName = new QLineEdit;
    m_pSearchName->setFixedHeight(50);
    QHBoxLayout *search = new QHBoxLayout;
    search->addWidget(m_pSearchName);
    search->addWidget(m_pSearchUsrPB);

    QHBoxLayout *pTopHBL =new QHBoxLayout;
    QSpacerItem *space1 = new QSpacerItem(0,0);
    QSpacerItem *space2 = new QSpacerItem(0,0);
    QSpacerItem *space3 = new QSpacerItem(0,0);
    QSpacerItem *space4 = new QSpacerItem(0,0);
    m_pShowOnlineUsrPB->setFixedSize(200,50);
    m_pPrivateChatPB->setFixedSize(200,50);
    pTopHBL->addWidget(m_pShowOnlineUsrPB);
    pTopHBL->addItem(space1);
    pTopHBL->addWidget(m_pPrivateChatPB);
    pTopHBL->addItem(space2);
    pTopHBL->addLayout(search);
    pTopHBL->addItem(space4);
    pTopHBL->addWidget(m_pDelFriendPB);
    pTopHBL->addItem(space3);
    pTopHBL->addWidget(m_pFlushFriendPB);

    QHBoxLayout *pMsgHBL = new QHBoxLayout;
    pMsgHBL->addWidget(m_pInputMsgLE);
    pMsgHBL->addWidget(m_pMsgSendPB);

    m_pOnline = new Online;
    m_pOnline->setWindowTitle("在线用户");
    m_pOnline->hide();


    QVBoxLayout *pRight = new QVBoxLayout;
    pRight->addWidget(m_pShowMsgTE);
    pRight->addLayout(pMsgHBL);

    QHBoxLayout *pCentreHBL =new QHBoxLayout;
    m_pFriendListWidget->setFixedWidth(200);
    m_pFriendListWidget->setFont(QFont("Arial",10));
    m_pShowMsgTE->setMinimumSize(400,500);
    pCentreHBL->addWidget(m_pFriendListWidget);
    pCentreHBL->addLayout(pRight);

    QVBoxLayout *pMain = new QVBoxLayout;
    pMain->addLayout(pTopHBL);
    pMain->addLayout(pCentreHBL);

    setLayout(pMain); 

    connect(m_pShowOnlineUsrPB,SIGNAL(clicked(bool)),this,SLOT(showOnline()));
    connect(m_pSearchUsrPB, SIGNAL(clicked(bool)), this,SLOT(searchUsr()));
    connect(m_pFlushFriendPB, SIGNAL(clicked(bool)), this, SLOT(flushFriend()));
    connect(m_pDelFriendPB, SIGNAL(clicked(bool)), this, SLOT(delFriend()));
    connect(m_pPrivateChatPB, SIGNAL(clicked(bool)), this, SLOT(privateChat()));
    connect(m_pMsgSendPB, SIGNAL(clicked(bool)), this, SLOT(groupChat()));
    connect(m_pFriendListWidget,&QListWidget::itemDoubleClicked,this,&Friend::privateChat);

    m_pFriendListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_pFriendListWidget,&QListWidget::customContextMenuRequested,[=](const QPoint& pos){
        QMenu* pMenu = new QMenu(m_pFriendListWidget);
        QAction *pPriChat = new QAction("私聊",pMenu);
        QAction *pDelte = new QAction("删除好友",pMenu);
        QAction *pFlush = new QAction("刷新列表",pMenu);

        if(m_pFriendListWidget->itemAt(pos) != NULL)
        {
            pMenu->addAction(pPriChat);
            pMenu->addAction(pDelte);
        }
        else
        {
             pMenu->addAction(pFlush);
        }
        connect(pPriChat,SIGNAL(triggered(bool)),this,SLOT(privateChat()));
        connect(pDelte,SIGNAL(triggered(bool)),this,SLOT(delFriend()));
        connect(pFlush,SIGNAL(triggered(bool)),this,SLOT(flushFriend()));

        pMenu->exec(QCursor::pos());

        delete pMenu;
    });
}

void Friend::showAllOnlineUsr(PDU *pdu)
{
    if(pdu == NULL)
    {
        return;
    }
    m_pOnline->showUsr(pdu);
}

void Friend::updateFriendList(PDU *pdu)
{
    if(pdu == NULL)
    {
        return;
    }
    m_pFriendListWidget->clear();
    uint uiSize = pdu->uiMsgLen/32;
    char caName[32]= {'\0'};
    for(uint i=0; i<uiSize; i++)
    {
        QListWidgetItem *listItem = new QListWidgetItem();
        m_pFriendListWidget->addItem(listItem);

        QWidget *widget = new QWidget();
        QHBoxLayout *hLayout = new QHBoxLayout(widget);
        hLayout->setSpacing(0);
        hLayout->setContentsMargins(0,0,0,0);

        QLabel *name = new QLabel;
        QLabel *stat = new QLabel;
        stat->setFixedSize(30,30);
        QPixmap *pixmap = new QPixmap;
        //读取好友名字
        memcpy(caName, (char*)(pdu->caMsg)+i*32, 32);
        if(caName[strlen(caName)-1] == '1')
        {
            caName[strlen(caName)-1] = '\0';
            name->setText(caName);
            pixmap->load(":/map/online.png");
        }
        else if(caName[strlen(caName)-1] == '0')
        {
            caName[strlen(caName)-1] = '\0';
            name->setText(caName);
            pixmap->load(":/map/offline.png");
        }
        pixmap->scaled(stat->size(),Qt::KeepAspectRatio);
        stat->setScaledContents(true);
        stat->setPixmap(*pixmap);

        hLayout->addWidget(name);
        hLayout->addWidget(stat);

        m_pFriendListWidget->setItemWidget(listItem,widget);

        //delete listItem;
//        m_pFriendListWidget->addItem(caName);
    }

}

void Friend::updateGroupMsg(PDU *pdu)
{
    QString strMsg = QString("%1:%2").arg(pdu->caData).arg((char*)(pdu->caMsg));
    m_pShowMsgTE->append(strMsg);
}

QListWidget *Friend::getFriendLW() const
{
    return m_pFriendListWidget;
}

PrivateChat *Friend::searchPriChat(const char *chatName)
{
    for(PrivateChat *ptr:m_priChatList)
    {
        if(ptr->chatName() == chatName)
        {
            return ptr;
        }
    }
    return NULL;
}

void Friend::insertPriChatToList(PrivateChat *priChat)
{
    m_priChatList.append(priChat);
}

void Friend::showOnline()
{
    if(m_pOnline->isHidden())
    {
        m_pOnline->show();
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType = ENUM_MSG_TYPE_ALL_ONLINE_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
    else
    {
        m_pOnline->hide();
    }
}

void Friend::searchUsr()
{
    m_strSearchName = m_pSearchName->text();
    m_pSearchName->clear();
    if(!m_strSearchName.isEmpty())
    {
        qDebug() << m_strSearchName;
        PDU *pdu = mkPDU(0);
        memcpy(pdu->caData, m_strSearchName.toStdString().c_str(), m_strSearchName.size());
        pdu->uiMsgType = ENUM_MSG_TYPE_SEARCH_USR_REQUEST;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Friend::flushFriend()
{
    QString strName = TcpClient::getInstance().loginName();
    PDU *pdu =mkPDU(0);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST;
    memcpy(pdu->caData, strName.toStdString().c_str(), strName.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Friend::delFriend()
{
    if(m_pFriendListWidget->currentItem() != NULL)
    {
        QString strFriendName = m_pFriendListWidget->currentItem()->text();
        PDU *pdu = mkPDU(0);
        pdu->uiMsgType =ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST;
        QString strSelfName = TcpClient::getInstance().loginName();
        memcpy(pdu->caData, strSelfName.toStdString().c_str(), strSelfName.size());
        memcpy(pdu->caData+32, strFriendName.toStdString().c_str(), strFriendName.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }

}

void Friend::privateChat()
{
    if(m_pFriendListWidget->currentItem() == NULL)
    {
        return;
    }

    QString strChatName = m_pFriendListWidget->findChild<QLabel*>()->text();
    //QString strChatName = m_pFriendListWidget->currentItem()->text();
    strChatName = strChatName.split("\t")[0];
    qDebug() << "private chat name:" << strChatName;

    PrivateChat *priChat = searchPriChat(strChatName.toStdString().c_str());
    if(priChat == NULL)
    {
        qDebug() << "创建新的对话";
        priChat = new PrivateChat;
        priChat->setChatName(strChatName);
        priChat->setWindowTitle(strChatName);
        m_priChatList.append(priChat);
    }
    if(priChat->isHidden())
    {
        priChat->show();
    }

}

void Friend::groupChat()
{
    QString strMsg = m_pInputMsgLE->text();
    m_pInputMsgLE->clear();
    if(!strMsg.isEmpty())
    {
        PDU *pdu = mkPDU(strMsg.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_GROUP_CHAT_REQUEST;
        QString strName = TcpClient::getInstance().loginName();
        strncpy(pdu->caData, strName.toStdString().c_str(), strName.size());
        strncpy((char*)pdu->caMsg, strMsg.toStdString().c_str(), strMsg.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        m_pShowMsgTE->append(strName + ":" + strMsg);
    }
    else
    {
        QMessageBox::warning(this, "群聊", "信息不能为空");
    }
}
