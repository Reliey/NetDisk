#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include "protocol.h"

namespace Ui {
class TcpClient;
}

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();
    void loadConfig();

    static TcpClient &getInstance();
    QTcpSocket &getTcpSocket();
    QString loginName();
    QString curPath();
    void setCurPath(QString strCurPath);

public slots:
    void showConnect();

private slots:
    //void on_send_pb_clicked();
    void recvMsg();
    void on_login_pb_clicked();

    void on_regist_pb_clicked();

    void on_cancel_pb_clicked();

private:
    Ui::TcpClient *ui;
    QString m_strIP;
    quint16 m_usPort;

    // 连接服务器，和服务器数据交互
    QTcpSocket m_tcpSocket;
    QString m_strLoginName;

    QString m_strCurPath;
    QFile m_file;
};

#endif // TCPCLIENT_H
