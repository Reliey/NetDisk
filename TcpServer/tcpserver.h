#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include "opedb.h"
namespace Ui {
class TcpServer;
}

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();
    void loadConfig();

private:
    Ui::TcpServer *ui;
    QString m_strIP;
    quint16 m_usPort;
};

#endif // TCPSERVER_H
