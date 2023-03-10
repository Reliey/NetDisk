#include "privatechat.h"
#include "ui_privatechat.h"
#include "protocol.h"
#include "tcpclient.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
PrivateChat::PrivateChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivateChat)
{
    ui->setupUi(this);

    setWindowTitle(m_strChatName);

    ui->inputMsg_le->setFocus();
    ui->sendMsg_pb->setShortcut(Qt::Key_Return);
    ui->showMsg_te->setTextInteractionFlags(Qt::NoTextInteraction);

}

PrivateChat::~PrivateChat()
{
    delete ui;
}

PrivateChat &PrivateChat::getInstance()
{
    static PrivateChat instance;
    return instance;
}

void PrivateChat::setChatName(QString strName)
{
    m_strChatName = strName;
    m_strLoginName = TcpClient::getInstance().loginName();
}

void PrivateChat::updateMsg(const PDU *pdu)
{
    //将读取到的消息显示上去出现问题
    if(pdu == NULL)
    {
        qDebug() << "pdu is null";
        return;
    }
    qDebug() << "pdu is not null";
    char caSendName[32] = {'\0'};
    memcpy(caSendName, pdu->caData, 32);
    QString strMsg = QString("%1 : %2").arg(caSendName).arg((char*)(pdu->caMsg));
    QByteArray byte = strMsg.toUtf8();
    ui->showMsg_te->append(byte);
}

QString PrivateChat::chatName() const
{
    return m_strChatName;
}

void PrivateChat::on_sendMsg_pb_clicked()
{
    QString strMsg = ui->inputMsg_le->text();
    ui->inputMsg_le->clear();
    if(!strMsg.isEmpty())
    {
        QString myMsg = QString(strMsg);
        QString myMsgDis = QString("%1 : %2").arg(TcpClient::getInstance().loginName()).arg(strMsg);
        QByteArray byte = myMsg.toUtf8();
        QByteArray byteDis = myMsgDis.toUtf8();
        ui->showMsg_te->append(byteDis);
        PDU *pdu = mkPDU(byte.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST;
        memcpy(pdu->caData, m_strLoginName.toStdString().c_str(), m_strLoginName.size());
        memcpy(pdu->caData+32, m_strChatName.toStdString().c_str(), m_strChatName.size());

        strcpy((char*)(pdu->caMsg), byte.toStdString().c_str());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
    else
    {
        QMessageBox::warning(this, "私聊", "发送的聊天信息不能为空");
    }
}
