#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
typedef unsigned int uint;
#define REGIST_OK "regist ok"
#define REGIST_FAILED "regist failed: name existed"

#define LOGIN_OK "login ok"
#define LOGIN_FAILED "login failed: name or pwd error or relogin"

#define SEARCH_USR_NO "no such people"
#define SEARCH_USR_ONLINE "online"
#define SEARCH_USR_OFFLINE "offline"

#define UNKNOW_ERROR "unknow error"
#define EXISTED_FRIEND "friend exist"
#define ADD_FRIEND_OFFLINE "usr offline"
#define ADD_FRIEND_NOEXISTED "usr not existed"

#define DEL_FRIEND_OK "delete friend ok"

#define DIR_NO_EXIST "current dir not exist"
#define FILE_NAME_EXIST "file name exist"
#define CREATE_DIT_OK "create dir ok"

#define DEL_DIR_OK "delete dir ok"
#define DEL_DIR_FAILED "delete dir failed: is regular file"

#define RENAME_FILE_OK "rename file ok"
#define RENAME_FILE_FAILED "rename file failed"

#define ENTER_DIR_OK "enter dir ok"
#define ENTER_DIR_FAILED "enter dir failed: is regular file"

#define UPLOAD_FILE_OK "upload file success"
#define UPLOAD_FILE_FAILED "upload file failed"

#define DEL_FILE_OK "delete file ok"
#define DEL_FILE_FAILED "delete file failed: is dir"

#define MOVE_FILE_OK "move file success"
#define MOVE_FILE_FAILED "move file failed: is regular file"

#define COMMON_ERROR "operate failed: system is busy"
enum ENUM_MSG_TYPE
{
    ENUM_MSG_TYPE_MIN = 0,
    ENUM_MSG_TYPE_REGIST_REQUEST,//注册请求
    ENUM_MSG_TYPE_REGIST_RESPOND,//注册回复

    ENUM_MSG_TYPE_LOGIN_REQUEST,//登录请求
    ENUM_MSG_TYPE_LOGIN_RESPOND,//登录回复

    ENUM_MSG_TYPE_ALL_ONLINE_REQUEST,//在线用户查看请求
    ENUM_MSG_TYPE_ALL_ONLINE_RESPOND,//在线用户查看回复

    ENUM_MSG_TYPE_SEARCH_USR_REQUEST,//搜索用户请求
    ENUM_MSG_TYPE_SEARCH_USR_RESPOND,//搜索用户回复

    ENUM_MSG_TYPE_ADD_FRIEND_REQUEST,//加好友请求
    ENUM_MSG_TYPE_ADD_FRIEND_RESPOND,//加好友回复

    ENUM_MSG_TYPE_ADD_FRIEND_AGREE, //同意加好友
    ENUM_MSG_TYPE_ADD_FRIEND_REFUSE,//拒绝加好友

    ENUM_MSG_TYPE_FLUSH_FRIEND_REQUEST, //刷新好友请求
    ENUM_MSG_TYPE_FLUSH_FRIEND_RESPOND,//刷新好友回复

    ENUM_MSG_TYPE_DELETE_FRIEND_REQUEST, //删除好友请求
    ENUM_MSG_TYPE_DELETE_FRIEND_RESPOND,//删除好友回复

    ENUM_MSG_TYPE_PRIVATE_CHAT_REQUEST, //私聊请求
    ENUM_MSG_TYPE_PRIVATE_CHAT_RESPOND,//私聊回复

    ENUM_MSG_TYPE_GROUP_CHAT_REQUEST, //群聊请求
    ENUM_MSG_TYPE_GROUP_CHAT_RESPOND,//群聊回复

    ENUM_MSG_TYPE_CREATE_DIR_REQUEST, //创建路径请求
    ENUM_MSG_TYPE_CREATE_DIR_RESPOND,//创建路径回复

    ENUM_MSG_TYPE_FLUSH_FILE_REQUEST, //刷新文件请求
    ENUM_MSG_TYPE_FLUSH_FILE_RESPOND,//刷新文件回复

    ENUM_MSG_TYPE_DEL_DIR_REQUEST, //删除文件夹请求
    ENUM_MSG_TYPE_DEL_DIR_RESPOND,//删除文件夹回复

    ENUM_MSG_TYPE_RENAME_FILE_REQUEST, //重命名文件请求
    ENUM_MSG_TYPE_RENAME_FILE_RESPOND,//重命名文件回复

    ENUM_MSG_TYPE_ENTER_DIR_REQUEST, //进入文件夹请求
    ENUM_MSG_TYPE_ENTER_DIR_RESPOND,//进入文件夹回复

    ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST, //上传文件请求
    ENUM_MSG_TYPE_UPLOAD_FILE_RESPOND,//上传文件回复

    ENUM_MSG_TYPE_DEL_FILE_REQUEST, //删除常规文件请求
    ENUM_MSG_TYPE_DEL_FILE_RESPOND,//删除常规文件回复

    ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST, //下载文件请求
    ENUM_MSG_TYPE_DOWNLOAD_FILE_RESPOND,//下载文件回复

    ENUM_MSG_TYPE_SHARE_FILE_REQUEST, //共享文件请求
    ENUM_MSG_TYPE_SHARE_FILE_RESPOND,//共享文件回复

    ENUM_MSG_TYPE_SHARE_FILE_NOTE, //共享文件通知
    ENUM_MSG_TYPE_SHARE_FILE_NOTE_RESPOND, //共享文件通知回复

    ENUM_MSG_TYPE_MOVE_FILE_REQUEST, //移动文件请求
    ENUM_MSG_TYPE_MOVE_FILE_RESPOND, //移动文件回复
//    ENUM_MSG_TYPE_REQUEST,
//    ENUM_MSG_TYPE_RESPOND,
    ENUM_MSG_TYPE_MAX = 0x00ffffff
};

struct FileInfo
{
    char caFileName[32]; //文件名字
    int iFileType; //文件类型
};

struct PDU
{
    uint uiPDULen; //总的协议数据单元大小
    uint uiMsgType; //消息类型
    char caData[64]; //文件名
    uint uiMsgLen; //消息长度
    int caMsg[]; //实际消息
};

PDU *mkPDU(uint uiMsgLen);

#endif // PROTOCOL_H
