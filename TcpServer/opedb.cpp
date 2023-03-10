#include "opedb.h"
#include <Qdebug>
OpeDB::OpeDB(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

OpeDB &OpeDB::getInstance()
{
    static OpeDB instance;
    return instance;
}

void OpeDB::init()
{
    m_db.setHostName("localhost");
    m_db.setDatabaseName("C:\\Qt\\NetDisk\\TcpServer\\cloud.db");
    if(m_db.open())
    {
        QSqlQuery query;
        query.exec("select * from usrInfo");
        while(query.next())
        {
            QString data = QString("%1,%2,%3").arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString());
            qDebug()<<data;
        }
    }
    else
    {
        QMessageBox::critical(NULL,"打开数据块","打开数据块失败");
    }
}

OpeDB::~OpeDB()
{
    m_db.close();
}

bool OpeDB::handleRegist(const char *name, const char *pwd)
{
    if(name == NULL || pwd == NULL)
    {
        return false;
    }
    QString data = QString("insert into usrInfo(name,pwd) values(\'%1\',\'%2\')").arg(name).arg(pwd);
    QSqlQuery query;
    return query.exec(data);

}

bool OpeDB::handleLogin(const char *name, const char *pwd)
{
    if(name == NULL || pwd == NULL)
    {
        return false;
    }
    QString data = QString("select * from usrInfo where name=\'%1\' and pwd=\'%2\' and online=0").arg(name).arg(pwd);
    QSqlQuery query;
    query.exec(data);
    if(query.next())
    {
        data = QString("update usrInfo set online=1 where name=\'%1\' and pwd=\'%2\' ").arg(name).arg(pwd);
        QSqlQuery query;
        query.exec(data);
        return true;
    }
    else
    {
        return false;
    }
}

void OpeDB::handleOffline(const char *name)
{
    if(name == NULL)
    {
        return;
    }
    QString data = QString("update usrInfo set online=0 where name=\'%1\' ").arg(name);
    QSqlQuery query;
    query.exec(data);
}

QStringList OpeDB::handleAllOnline()
{
    QString data = QString("select name from usrInfo where online=1 ");
    QSqlQuery query;
    query.exec(data);
    QStringList result;
    result.clear();

    while(query.next())
    {
        result.append(query.value(0).toString());
    }
    return result;
}

int OpeDB::handleSearchUsr(const char *name)
{
    if(name == NULL)
    {
        return -1;
    }
    QString data = QString("select online from usrInfo where name = \'%1\' ").arg(name);
    QSqlQuery query;
    query.exec(data);

    if(query.next())
    {
        int ret = query.value(0).toInt();
        return ret;
    }
    else
    {
        return -1;
    }
}

int OpeDB::handleAddFriend(const char *pername, const char *name)
{
    if(pername == NULL || name == NULL)
    {
        return -1;;
    }
    QString data = QString("select * from friend where (id = (select id from usrInfo where name = \'%1\') and friendId = (select id from usrInfo where name = \'%2\')) "
                           "or (id = (select id from usrInfo where name = \'%3\') and friendId = (select id from usrInfo where name = \'%4\'))").arg(pername).arg(name).arg(name).arg(pername);
    qDebug() << data;
    QSqlQuery query;
    query.exec(data);
    if(query.next())
    {
        return 0; //双方已是好友
    }
    else
    {
        QString data = QString("select online from usrInfo where name = \'%1\' ").arg(pername);
        QSqlQuery query;
        query.exec(data);

        if(query.next())
        {
            int ret = query.value(0).toInt();
            if(ret == 1)
            {
                qDebug() << "在线";
                return 1; //在线

            }
            else if(ret == 0)
            {
                return 2; //不在线
            }
        }
        else
        {
            return 3; //不存在
        }
    }
}

void OpeDB::handleAddFriendAgree(const char *pername, const char *name)
{
    if(name == NULL || pername == NULL)
    {
        return;
    }
    int FriendId = -1, UsrId = -1;
    FriendId = getIdByUsrName(pername);
    UsrId = getIdByUsrName(name);
    QString data = QString("insert into friend values(%1, %2) ").arg(FriendId).arg(UsrId);
    QSqlQuery query;
    query.exec(data);
}

int OpeDB::getIdByUsrName(const char *name)
{
    if(NULL == name)
    {
        return -1;
    }
    QString strQuery = QString("select id from usrInfo where name = \'%1\' ").arg(name);
    QSqlQuery query;
    query.exec(strQuery);
    if(query.next())
    {
        return query.value(0).toInt();
    }
    else
    {
        return -1; // 不存在该用户
    }
}

QStringList OpeDB::handleFlushFriend(const char *name)
{
    QStringList strFriendList;
    strFriendList.clear();
    if(name == NULL)
    {
        return strFriendList;
    }

    QString data = QString("select id from usrInfo where name = \'%1\' ").arg(name);
    QSqlQuery query;
    query.exec(data);
    int iId = -1;
    if(query.next())
    {
        iId = query.value(0).toInt();
    }
    qDebug() << iId;

    data = QString("select name from usrInfo where online=1 and "
                   "id in (select id from friend where friendId = %1)").arg(iId);
//    qDebug() <<data;
    query.exec(data);
    while(query.next())
    {
//        qDebug() <<query.value(0).toString();
        strFriendList.append(query.value(0).toString());
    }
    data = QString("select name from usrInfo where online=1 and "
                   "id in (select friendId from friend where id = %1)").arg(iId);
    query.exec(data);
    while(query.next())
    {
        qDebug() <<query.value(0).toString();
        strFriendList.append(query.value(0).toString());
    }
    return strFriendList;
}

bool OpeDB::handleDelFriend(const char *name, const char *friendName)
{
    if(name == NULL || friendName == NULL)
    {
        return false;
    }
    QString data = QString("delete from friend where id = (select id from usrInfo where name = \'%1\') "
                           "and friendId =(select id from usrInfo where name = \'%2\')").arg(name).arg(friendName);
    QSqlQuery query;
    query.exec(data);
    qDebug() <<data;
    data = QString("delete from friend where id = (select id from usrInfo where name = \'%1\') "
                   "and friendId =(select id from usrInfo where name = \'%2\')").arg(friendName).arg(name);
    query.exec(data);
    return true;
}

