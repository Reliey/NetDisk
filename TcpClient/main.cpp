#include "tcpclient.h"
#include "opewidget.h"
#include <QApplication>
#include <QMessageBox>
//#include "online.h"
#include "friend.h"
#include "sharefile.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("Times", 18, QFont::Bold);
    a.setFont(font);
//    TcpClient w;
//    w.show();

    TcpClient::getInstance().show();

//    QMessageBox::information(NULL, "添加好友", "6666", QMessageBox::Yes, QMessageBox::No);
//    ShareFile w;
//    w.show();

//      OpeWidget w;
//      w.show();
//    Book w;
//    w.show();

    return a.exec();
}
