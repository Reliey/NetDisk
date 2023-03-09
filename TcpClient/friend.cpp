#include "friend.h"
#include "tcpclient.h"
#include <QInputDialog>
#include <QDebug>
#include <QMessageBox>

Friend::Friend(QWidget *parent) : QWidget(parent)
{
    m_pShowMsgTE = new QTextEdit;
    m_pFriendListWidget = new QListWidget;
    m_pInputMsgLE = new QLineEdit;

    m_pDelFriendPB = new QPushButton("删除好友");
    m_pFlushFriendPB = new QPushButton("刷新好友");
    m_pShowOnlineUsrPB = new QPushButton("显示在线用户");
    m_pSearchUsrPB = new QPushButton("查找用户");
    m_pMsgSendPB = new QPushButton("信息发送");
    m_pPrivateChatPB = new QPushButton("私聊");

    m_pDelFriendPB->hide();
    m_pPrivateChatPB->hide();

//    QVBoxLayout *pRightPBVBL = new QVBoxLayout;
//    pRightPBVBL->addWidget(m_pDelFriendPB);
//    pRightPBVBL->addWidget(m_pFlushFriendPB);
//    pRightPBVBL->addWidget(m_pShowOnlineUsrPB);
//    pRightPBVBL->addWidget(m_pSearchUsrPB);
//    pRightPBVBL->addWidget(m_pPrivateChatPB);

    QHBoxLayout *pTopHBL =new QHBoxLayout;
    pTopHBL->addWidget(m_pShowOnlineUsrPB);
    pTopHBL->addWidget(m_pSearchUsrPB);
    pTopHBL->addWidget(m_pFlushFriendPB);

    m_pShowOnlineUsrPB->setStyleSheet("border:none;"
                                      "text-align: left;"
                                      "font-family:'Arial';"
                                      "font-size:18px;");
    m_pShowOnlineUsrPB->setFixedSize(115,30);
    m_pSearchUsrPB->setStyleSheet("border:none;"
                                      "text-align: left;"
                                      "font-family:'Arial';"
                                      "font-size:18px;");
    m_pSearchUsrPB->setFixedSize(115,30);
    m_pFlushFriendPB->setStyleSheet("border:none;"
                                      "text-align: left;"
                                      "font-family:'Arial';"
                                      "font-size:18px;");
    m_pFlushFriendPB->setFixedSize(115,30);

    QHBoxLayout *pCentreHBL =new QHBoxLayout;
    pCentreHBL->addWidget(m_pFriendListWidget);
    pCentreHBL->addWidget(m_pShowMsgTE);
    //pCentreHBL->addLayout(pRightPBVBL);

    QHBoxLayout *pMsgHBL = new QHBoxLayout;
    pMsgHBL->addWidget(m_pInputMsgLE);
    pMsgHBL->addWidget(m_pMsgSendPB);

    m_pOnline = new Online;

    QVBoxLayout *pMain = new QVBoxLayout;
    pMain->addLayout(pTopHBL);
    pMain->addLayout(pCentreHBL);
    pMain->addLayout(pMsgHBL);
    pMain->addWidget(m_pOnline);
    m_pOnline->hide();

    setLayout(pMain);

    connect(m_pShowOnlineUsrPB,SIGNAL(clicked(bool)),this,SLOT(showOnline()));
    connect(m_pSearchUsrPB, SIGNAL(clicked(bool)), this,SLOT(searchUsr()));
    connect(m_pFlushFriendPB, SIGNAL(clicked(bool)), this, SLOT(flushFriend()));
    connect(m_pDelFriendPB, SIGNAL(clicked(bool)), this, SLOT(delFriend()));
    connect(m_pPrivateChatPB, SIGNAL(clicked(bool)), this, SLOT(privateChat()));
    connect(m_pMsgSendPB, SIGNAL(clicked(bool)), this, SLOT(groupChat()));

    //设置QTextEdit上默认字体大小
    m_pShowMsgTE->setFont(QFont("Arial",12));
    //设置QTextEdit只读不可写
    m_pShowMsgTE->setReadOnly(true);
    //设置信息输入框字体大小
    m_pInputMsgLE->setFont(QFont("Arial",15));
    //设置好友列表字体大小
    m_pFriendListWidget->setFont(QFont("Arial",12));
    //设置QListWidget的contextMenuPolicy属性，不然不能显示右键菜单
    m_pFriendListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    m_pRightMenu = new QMenu(m_pFriendListWidget);
    m_pRightMenu->setFont(QFont("Arial",12));
    m_pDelFriend = new QAction("删除",m_pFriendListWidget);
    m_pRightMenu->addAction(m_pDelFriend);

    connect(m_pFriendListWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showMenu(QPoint)));
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
        memcpy(caName, (char*)(pdu->caMsg)+i*32, 32);
        m_pFriendListWidget->addItem(caName);
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

void Friend::showMenu(const QPoint& pos)
{
    QPoint globalPos = m_pFriendListWidget->mapToGlobal(pos);
    m_pRightMenu->exec(globalPos);
}

//void Friend::onContextMenuEvent(QAction *action)
//{
//    if(action->text() == "刷新"){
//        qDebug() << "要刷新好友";
//    }
//}

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
    m_strSearchName = QInputDialog::getText(this, "搜索", "用户名：");
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
//    qDebug() << strName;
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
//        QMessageBox::warning(this, "私聊", "请选择私聊对象");
        return;
    }

    QString strChatName = m_pFriendListWidget->currentItem()->text();
    strChatName = strChatName.split("\t")[0];

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
    QString name = TcpClient::getInstance().loginName();
    m_pShowMsgTE->append(name + "：" + strMsg);
    if(!strMsg.isEmpty())
    {
        PDU *pdu = mkPDU(strMsg.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_GROUP_CHAT_REQUEST;
        QString strName = TcpClient::getInstance().loginName();
        strncpy(pdu->caData, strName.toStdString().c_str(), strName.size());
        strncpy((char*)pdu->caMsg, strMsg.toStdString().c_str(), strMsg.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
    }
    else
    {
        QMessageBox::warning(this, "群聊", "信息不能为空");
    }
    m_pInputMsgLE->clear();
}
