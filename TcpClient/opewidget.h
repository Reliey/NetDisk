#ifndef OPEWIDGET_H
#define OPEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include "friend.h"
#include "book.h"
#include <QStackedWidget>
#include <QLabel>
class OpeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpeWidget(QWidget *parent = nullptr);
    static OpeWidget &getInstance();
    Friend *getFriend();
    Book *getBook();
//    void add_ListWidgetItem();
    bool eventFilter(QObject *obj, QEvent *event) override;
    void setHand();
signals:

public slots:

private:
    QListWidget *m_pListW;
    Friend *m_pFriend;
    Book *m_pBook;
    QStackedWidget *m_pSW;
    QLabel *m_profile;
    QLabel *m_name;
    QFrame *m_vframe;
    QFrame *m_hframe;
};

#endif // OPEWIDGET_H
