#ifndef SEL_USER_ACCOUNT_WIDGET_H
#define SEL_USER_ACCOUNT_WIDGET_H

#include <QtGui/QWidget>

class QTableWidget;
class QTableWidgetItem;
class QPushButton;
class QLineEdit;
class QLabel;

class LoanRequest;
class SELController;

/**
 *  @class  SELUserAccountWidget
 */
class SELUserAccountWidget : public QWidget {
Q_OBJECT

private:
    ///
    SELController & controller;
    ///
    QLabel * usernameLabel;
    ///
    QLabel * emailLabel;
    ///
    QLabel * currentPageLabel;
    ///
    QTableWidget * messageTableWidget;
    ///
    QLineEdit * usernameLineEdit;
    ///
    QLineEdit * emailLineEdit;
    ///
    QPushButton * updateDataButton;
    ///
    QPushButton * nextPageButton;
    ///
    QPushButton * previousPageButton;
    ///
    unsigned long long * requestIds;
    
    ///
    unsigned long long findId(QTableWidgetItem * item);

public:
    ///
    static const int ROWS_PER_PAGE;
    ///
    static const int NUM_COLUMNS;
    
    ///
    SELUserAccountWidget(SELController & controller, QWidget * parent = 0);
    ///
    virtual ~SELUserAccountWidget();
    
public slots:
    ///
    void updateMessagesTable(LoanRequest ** requests, unsigned numRequests);
    ///
    void loadUserData();
    
private slots:
    ///
    void updatePageIndexNext();
    ///
    void updatePageIndexPrevious();
    ///
    void emitIdShowData(QTableWidgetItem * item);

signals:
    ///
    void getUserMessagesPage(int page);
    ///
    void showRequestReplyDialog(unsigned long long id);
};

#endif /// Not SEL_USER_ACCOUNT_WIDGET_H
