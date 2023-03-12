#include "book.h"
#include "tcpclient.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QFrame>
#include "opewidget.h"
#include "sharefile.h"
Book::Book(QWidget *parent) : QWidget(parent)
{
    m_strEnterDir.clear();

    m_bDownload = false;

    m_pTimer = new QTimer;

    m_pBookListW = new QListWidget;
    m_vframe = new QFrame;
    m_pReturnPB = new QPushButton("返回");
    m_pCreateDirPB = new QPushButton("创建文件夹");
    m_pDelDirPB = new QPushButton("删除文件夹");
    m_pRenamePB = new QPushButton("重命名文件");
    m_pMoveFilePB = new QPushButton("移动文件");

    m_pAddMenuPB = new QPushButton;
    m_pAddMenu = new QMenu;
    QAction *upload = new QAction(QIcon(":/map/upload.png"),"上传文件",this);
    QAction *createDir = new QAction(QIcon(":/map/createdir.png"),"创建文件夹",this);
    m_pAddMenu->addAction(upload);
    m_pAddMenu->addAction(createDir);
    m_pAddMenuPB->setMenu(m_pAddMenu);
    m_pAddMenuPB->setFixedSize(40,40);
    m_pFlushFilePB = new QPushButton;
    m_pFlushFilePB->setFixedSize(40,40);
    m_pFlushFilePB->setStatusTip("刷新文件");

    m_vframe->setFrameShape(QFrame::VLine); //设置垂直线
    m_vframe->setFrameShadow(QFrame::Plain);

    QVBoxLayout *pDirVBL = new QVBoxLayout;
    pDirVBL->addWidget(m_pReturnPB);
    pDirVBL->addWidget(m_pCreateDirPB);
    pDirVBL->addWidget(m_pDelDirPB);
    pDirVBL->addWidget(m_pRenamePB);
    pDirVBL->addWidget(m_pMoveFilePB);

    m_pUploadPB = new QPushButton("上传文件");
    m_pDownloadPB = new QPushButton("下载文件");
    m_pDelFilePB = new QPushButton("删除文件");
    m_pShareFilePB = new QPushButton("共享文件");
    m_pSelectDirPB = new QPushButton("目标目录");
    m_pSelectDirPB->setEnabled(false);

    QVBoxLayout *pFileVBL = new QVBoxLayout;
    pFileVBL->addWidget(m_pUploadPB);
    pFileVBL->addWidget(m_pDownloadPB);
    pFileVBL->addWidget(m_pDelFilePB);
    pFileVBL->addWidget(m_pShareFilePB);
    pFileVBL->addWidget(m_pSelectDirPB);

    QHBoxLayout *operate = new QHBoxLayout;
    operate->setSpacing(20);
    operate->addWidget(m_pAddMenuPB);
    operate->addWidget(m_pFlushFilePB);
    m_pTopHorizonSp = new QSpacerItem(300,20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    operate->addItem(m_pTopHorizonSp);

    QVBoxLayout *pList = new QVBoxLayout;
    pList->addLayout(operate);
    pList->addWidget(m_pBookListW);

    QHBoxLayout *pMain = new QHBoxLayout;
//    pMain->addWidget(m_pBookListW);
    pMain->addLayout(pList);
    pMain->addWidget(m_vframe);
    pMain->addLayout(pDirVBL);
    pMain->addLayout(pFileVBL);


    setLayout(pMain);

    m_pBookListW->setObjectName("m_bookListW");
    m_pReturnPB->setObjectName("m_pReturnPB");
    m_pCreateDirPB->setObjectName("m_pCreateDirPB");
    m_pDelDirPB->setObjectName("m_pDelDirPB");
    m_pRenamePB->setObjectName("m_pRenamePB");
    m_pFlushFilePB->setObjectName("m_pFlushFilePB");
    m_pUploadPB->setObjectName("m_pUploadPB");
    m_pDownloadPB->setObjectName("m_pDownloadPB");
    m_pDelFilePB->setObjectName("m_pDelFilePB");
    m_pShareFilePB->setObjectName("m_pShareFilePB");
    m_pMoveFilePB->setObjectName("m_pMoveFilePB");
    m_pSelectDirPB->setObjectName("m_pSelectDirPB");
    m_pAddMenuPB->setObjectName("m_pAddMenuPB");

    connect(m_pCreateDirPB, SIGNAL(clicked(bool)), this, SLOT(createDir()));
    connect(m_pFlushFilePB, SIGNAL(clicked(bool)), this, SLOT(flushFile()));
    connect(m_pDelDirPB, SIGNAL(clicked(bool)), this, SLOT(delDir()));
    connect(m_pRenamePB, SIGNAL(clicked(bool)), this, SLOT(reNameFile()));
    connect(m_pBookListW, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(enterDir(QModelIndex)));
    connect(m_pReturnPB, SIGNAL(clicked(bool)), this, SLOT(returnPreDir()));
    connect(m_pUploadPB, SIGNAL(clicked(bool)), this, SLOT(uploadFile()));
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(uploadFileData()));
    connect(m_pDelFilePB, SIGNAL(clicked(bool)), this, SLOT(delRegFile()));
    connect(m_pDownloadPB, SIGNAL(clicked(bool)), this, SLOT(downloadFile()));
    connect(m_pShareFilePB, SIGNAL(clicked(bool)), this, SLOT(shareFile()));
    connect(m_pMoveFilePB, SIGNAL(clicked(bool)), this, SLOT(moveFile()));
    connect(m_pSelectDirPB, SIGNAL(clicked(bool)), this, SLOT(selectDesDir()));
    connect(upload, &QAction::triggered, this, &Book::uploadFile);
    connect(createDir,&QAction::triggered, this, &Book::createDir);

    m_pBookListW->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_pBookListW,&QListWidget::customContextMenuRequested,[=](const QPoint& pos)
    {
        QMenu *pMenu = new QMenu(m_pBookListW);
        QAction *pDelete = new QAction("删除文件", pMenu);
        QAction *pDownload = new QAction("下载", pMenu);
        QAction *pRename = new QAction("重命名", pMenu);
        QAction *pCollect = new QAction("收藏", pMenu);
        QAction *pCreateDir = new QAction(QIcon(":/map/createdir.png"),"新建文件夹", pMenu);
        QAction *pUpload = new QAction(QIcon(":/map/upload.png"),"上传文件", pMenu);
        QAction *pFlush = new QAction(QIcon(":/map/flush_black.png"),"刷新页面", pMenu);
        //当ListWidgetitem不为空时显示菜单
        if(m_pBookListW->itemAt(/*mapFromGlobal(QCursor::pos())*/pos)!=NULL)
        {
            pMenu->addAction(pDelete);
            pMenu->addAction(pDownload);
            pMenu->addAction(pRename);
            pMenu->addAction(pCollect);
        }
        else
        {
            pMenu->addAction(pCreateDir);
            pMenu->addSeparator(); //添加分隔符
            pMenu->addAction(pUpload);
            pMenu->addSeparator();
            pMenu->addAction(pFlush);
        }

        connect(pDelete,SIGNAL(triggered(bool)),this,SLOT(delRegFile()));
        connect(pDownload,SIGNAL(triggered(bool)),this,SLOT(downloadFile()));
        connect(pRename,SIGNAL(triggered(bool)),this,SLOT(reNameFile()));
        connect(pCreateDir,SIGNAL(triggered(bool)),this,SLOT(createDir()));
        connect(pUpload,SIGNAL(triggered(bool)),this,SLOT(uploadFile()));
        connect(pFlush,SIGNAL(triggered(bool)),this,SLOT(flushFile()));

        //在鼠标位置显示菜单
        pMenu->exec(QCursor::pos());

        delete pMenu;
    });
}

void Book::updateFileList(const PDU *pdu)
{

    if(pdu == NULL)
    {
        return;
    }
    //点击刷新文件后，需要将原来的信息清除掉，重新显示
    QListWidgetItem *pItemTmp = NULL;
    int row = m_pBookListW->count();
    while(m_pBookListW->count()>0)
    {
        pItemTmp = m_pBookListW->item(row-1);
        m_pBookListW->removeItemWidget(pItemTmp);
        delete pItemTmp;
        row = row - 1;
    }
    FileInfo *pFileInfo = NULL;
    int iCount = pdu->uiMsgLen/sizeof(FileInfo);
    for(int i=0; i<iCount; i++)
    {
        pFileInfo = (FileInfo*)(pdu->caMsg)+i;
        qDebug() << pFileInfo->caFileName << pFileInfo->iFileType;
        QListWidgetItem *pItem = new QListWidgetItem;
        if(pFileInfo->iFileType == 0)
        {
            pItem->setIcon(QIcon(QPixmap(":/map/dir.png")));
        }
        else if(pFileInfo->iFileType == 1)
        {
            pItem->setIcon(QIcon(QPixmap(":/map/regFile.png")));
        }
        pItem->setText(pFileInfo->caFileName);
        m_pBookListW->addItem(pItem);
    }

}

void Book::clearEnterDir()
{
    m_strEnterDir.clear();
}

QString Book::enDir()
{
    return m_strEnterDir;
}

void Book::setDownloadStatus(bool status)
{
    m_bDownload = status;
}

bool Book::getDownloadStatus()
{
    return m_bDownload;
}

QString Book::getSaveFilePath()
{
    return m_strSaveFilePath;
}

QString Book::getShareFileName()
{
    return m_strShareFileName;
}

void Book::createDir()
{
    QString strNewDir = QInputDialog::getText(this, "新建文件", "新文件夹名字");
    if(!strNewDir.isEmpty())
    {
        if(strNewDir.size()>32)
        {
            QMessageBox::warning(this, "新建文件夹", "新文件夹名字不能超过32个字符");
        }
        else
        {
            QString strName = TcpClient::getInstance().loginName();
            QString strCurPath = TcpClient::getInstance().curPath();

            PDU *pdu = mkPDU(strCurPath.size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_CREATE_DIR_REQUEST;
            strncpy(pdu->caData, strName.toStdString().c_str(), strName.size());
            strncpy(pdu->caData+32, strNewDir.toStdString().c_str(), strNewDir.size());
            memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
            TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
            free(pdu);
            pdu = NULL;
        }
    }
    else
    {
        QMessageBox::warning(this, "新建文件夹", "新文件夹名字不能为空");
    }
}

void Book::flushFile()
{
    clearEnterDir();
    QString strCurPath = TcpClient::getInstance().curPath();
    qDebug() << "现在路径" << TcpClient::getInstance().curPath();
    PDU *pdu = mkPDU(strCurPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_FLUSH_FILE_REQUEST;
    memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());

    TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::delDir()
{
    QString strCurPath = TcpClient::getInstance().curPath();
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL)
    {
        QMessageBox::warning(this, "删除文件", "请选择要删除的文件");
    }
    else
    {
        QString strDelName = pItem->text();
        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_DEL_DIR_REQUEST;
        memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
        memcpy(pdu->caData, strDelName.toStdString().c_str(), strDelName.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Book::reNameFile()
{
    QString strCurPath = TcpClient::getInstance().curPath();
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL)
    {
        QMessageBox::warning(this, "重命名文件", "请选择要重命名的文件");
    }
    else
    {
        QString strOldName = pItem->text();
        QString strNewName = QInputDialog::getText(this, "重命名文件", "请输入新的文件名：");
        if(!strNewName.isEmpty())
        {
            PDU *pdu = mkPDU(strCurPath.size()+1);
            pdu->uiMsgType = ENUM_MSG_TYPE_RENAME_FILE_REQUEST;
            memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
            memcpy(pdu->caData, strOldName.toStdString().c_str(), strOldName.size());
            memcpy(pdu->caData+32, strNewName.toStdString().c_str(), strNewName.size());

            TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
            free(pdu);
            pdu = NULL;
        }
        else
        {
            QMessageBox::warning(this, "重命名文件", "新文件名不能为空");
        }
    }
}

void Book::enterDir(const QModelIndex &index)
{
    QString strDirName = index.data().toString();
    m_strEnterDir = strDirName;
    QString strCurPath = TcpClient::getInstance().curPath();
    PDU *pdu = mkPDU(strCurPath.size()+1);
    pdu->uiMsgType = ENUM_MSG_TYPE_ENTER_DIR_REQUEST;
    memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
    memcpy(pdu->caData, strDirName.toStdString().c_str(), strDirName.size());
    TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
    free(pdu);
    pdu = NULL;
}

void Book::returnPreDir()
{
    QString strCurPath = TcpClient::getInstance().curPath();
    QString strRootPath = "./" + TcpClient::getInstance().loginName();
    if(strCurPath == strRootPath)
    {
        QMessageBox::warning(this, "返回", "返回失败：已经在最开始的文件夹目录下");
    }
    else
    {
        int index = strCurPath.lastIndexOf('/');//从后面往前找 / 返回值是int 删除这个值之后的字符
        strCurPath.remove(index, strCurPath.size() - index);
        qDebug() << "return -->" << strCurPath;
        TcpClient::getInstance().setCurPath(strCurPath);

        flushFile();
    }
}

void Book::uploadFile()
{
    QString strCurPath = TcpClient::getInstance().curPath();
    m_strUploadFilePath = QFileDialog::getOpenFileName();   //打开文件夹窗口并返回所选择文件的路径
    if(!m_strUploadFilePath.isEmpty())
    {
        int index = m_strUploadFilePath.lastIndexOf('/');
        QString strFileName = m_strUploadFilePath.right(m_strUploadFilePath.size()-index-1);

        QFile file(m_strUploadFilePath);
        qint64 fileSize = file.size(); //获得文件大小

        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_UPLOAD_FILE_REQUEST;
        memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
        sprintf(pdu->caData, "%s %lld", strFileName.toStdString().c_str(), fileSize);//将文件名和文件大小放入caData;
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;

        m_pTimer->start(1000);//启动定时器，定时器时间到后客户端在上传文件给服务器，避免要上传的文件和请求上传文件粘包
    }
    else
    {
        QMessageBox::warning(this, "上传文件", "上传文件名字不能为空");
    }

}

void Book::delRegFile()
{
    QString strCurPath = TcpClient::getInstance().curPath();
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL)
    {
        QMessageBox::warning(this, "删除文件", "请选择要删除的文件");
    }
    else
    {
        QString strDelName = pItem->text();
        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_DEL_FILE_REQUEST;
        memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
        memcpy(pdu->caData, strDelName.toStdString().c_str(), strDelName.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
}

void Book::downloadFile()
{

    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL)
    {
        QMessageBox::warning(this, "下载文件", "请选择要下载的文件");
    }
    else
    {
        QString strSaveFilePath = QFileDialog::getSaveFileName();
        if(strSaveFilePath.isEmpty())
        {
            QMessageBox::warning(this, "下载文件", "请选择保存的路径");
            m_strSaveFilePath.clear();
        }
        else
        {
            m_strSaveFilePath = strSaveFilePath;
        }

        QString strCurPath = TcpClient::getInstance().curPath();
        QString strFileName = pItem->text();
        PDU *pdu = mkPDU(strCurPath.size()+1);
        pdu->uiMsgType = ENUM_MSG_TYPE_DOWNLOAD_FILE_REQUEST;
        memcpy(pdu->caMsg, strCurPath.toStdString().c_str(), strCurPath.size());
        memcpy(pdu->caData, strFileName.toStdString().c_str(), strFileName.size());
        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);

        free(pdu);
        pdu = NULL;
    }
}

void Book::uploadFileData()
{
    m_pTimer->stop();
    QFile file(m_strUploadFilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "上传文件", "打开文件失败");
        return;
    }

    char *pBuffer = new char[4096];
    qint64 ret = 0;
    while(true)
    {
        ret = file.read(pBuffer, 4096);
        if(ret > 0 && ret <= 4096)
        {
            TcpClient::getInstance().getTcpSocket().write(pBuffer, ret);
        }
        else if(ret == 0)
        {
            break;
        }
        else
        {
            QMessageBox::warning(this, "上传文件", "上传文件失败:读文件失败");
            break;
        }
    }
    file.close();
    delete []pBuffer;
    pBuffer = NULL;
}

void Book::shareFile()
{
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL)
    {
        QMessageBox::warning(this, "分享文件", "请选择要分享的文件");
        return;
    }
    else
    {
        m_strShareFileName = pItem->text();
    }
    Friend *pFriend = OpeWidget::getInstance().getFriend();
    QListWidget *pFriendList = pFriend->getFriendLW();
    ShareFile::getInstance().updateFriend(pFriendList);
    if(ShareFile::getInstance().isHidden())
    {
        ShareFile::getInstance().show();
    }
}

void Book::moveFile()
{
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem == NULL)
    {
        QMessageBox::warning(this, "移动文件", "请选择要移动的文件");
        return;
    }
    else
    {
        m_strMoveFileName = pItem->text();
        QString strCurPath = TcpClient::getInstance().curPath();
        m_strMoveFilePath = strCurPath + "/" +m_strMoveFileName;
        m_pSelectDirPB->setEnabled(true);
    }
}

void Book::selectDesDir()
{
    QListWidgetItem *pItem = m_pBookListW->currentItem();
    if(pItem != NULL)
    {
        QString strDesDir = pItem->text();
        QString strCurPath = TcpClient::getInstance().curPath();
        m_strDesDir = strCurPath + "/" + strDesDir;

        int srcLen = m_strMoveFilePath.size();
        int desLen = m_strDesDir.size();

        PDU *pdu = mkPDU(srcLen+desLen+2);
        pdu->uiMsgType = ENUM_MSG_TYPE_MOVE_FILE_REQUEST;
        sprintf(pdu->caData, "%d %d %s", srcLen, desLen, m_strMoveFileName.toStdString().c_str());
        memcpy(pdu->caMsg, m_strMoveFilePath.toStdString().c_str(), srcLen);
        memcpy((char*)(pdu->caMsg)+srcLen+1, m_strDesDir.toStdString().c_str(), desLen);

        TcpClient::getInstance().getTcpSocket().write((char*)pdu, pdu->uiPDULen);
        free(pdu);
        pdu = NULL;
    }
    else
    {
        QMessageBox::warning(this, "移动文件", "请选择要移动的文件");
    }
    m_pSelectDirPB->setEnabled(false);
}
