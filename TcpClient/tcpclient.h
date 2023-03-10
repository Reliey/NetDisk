#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QFile>
#include <QTcpSocket>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMovie>
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

    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
    void initSystemTray();//初始化系统托盘
    void startGIF();//加载背景动态图
    void keyPressEvent(QKeyEvent *event);//重写回车函数，实现回车登录

public slots:
    void showConnect();

private slots:
    //void on_send_pb_clicked();
    void recvMsg();
    void on_login_pb_clicked();

    void on_regist_pb_clicked();

    void on_cancel_pb_clicked();

    void on_min_clicked();

    void on_close_clicked();

    //系统托盘右键
    void showWidget();
    //void closeWidget();
private:
    Ui::TcpClient *ui;
    QString m_strIP;
    quint16 m_usPort;

    // 连接服务器，和服务器数据交互
    QTcpSocket m_tcpSocket;
    QString m_strLoginName;

    QString m_strCurPath; //当前路劲
    QFile m_file;

    //和窗口移动相关
    bool isPressedWidget;
    QPoint last;

    QSystemTrayIcon *m_pSystemTrayIcon;//系统托盘

    //系统托盘右键点击
    QMenu *m_pMenu;
    QAction *m_pShowAction;
    QAction *m_pCloseAction;

    //登录背景动态图
    QMovie *m_pMovie;
};

#endif // TCPCLIENT_H
