#ifndef BOOK_H
#define BOOK_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QMenu>
#include "protocol.h"

class Book : public QWidget
{
    Q_OBJECT
public:
    explicit Book(QWidget *parent = nullptr);
    void updateFileList(const PDU *pdu);
    void clearEnterDir();
    QString enDir();
    void setDownloadStatus(bool status);
    bool getDownloadStatus();
    QString getSaveFilePath();
    QString getShareFileName();


    qint64 m_iTotal; //总文件大小
    qint64 m_iReceved; //已收到多少


signals:

public slots:
    void createDir();
    void flushFile();
    void delDir();
    void reNameFile();
    void enterDir(const QModelIndex &index);
    void returnPreDir();
    void uploadFile();
    void delRegFile();
    void downloadFile();

    void uploadFileData();

    void shareFile();
    void moveFile();
    void selectDesDir();


private:
    QListWidget *m_pBookListW;
    QPushButton *m_pReturnPB;
    QPushButton *m_pCreateDirPB;
    QPushButton *m_pDelDirPB;
    QPushButton *m_pRenamePB;
    QPushButton *m_pFlushFilePB;
    QPushButton *m_pUploadPB;
    QPushButton *m_pDownloadPB;
    QPushButton *m_pDelFilePB;
    QPushButton *m_pShareFilePB;
    QPushButton *m_pMoveFilePB;
    QPushButton *m_pSelectDirPB;
    QFrame *m_vframe;

    QString m_strEnterDir;
    QString m_strUploadFilePath;

    QTimer *m_pTimer;

    QString m_strSaveFilePath;
    bool m_bDownload;

    QString m_strShareFileName;
    QString m_strMoveFileName;
    QString m_strMoveFilePath;
    QString m_strDesDir;

    QPushButton *m_pAddMenuPB;
    QMenu *m_pAddMenu;
    QSpacerItem *m_pTopHorizonSp;

};

#endif // BOOK_H
