#ifndef SEL_USER_ACCOUNT_WIDGET_H
#define SEL_USER_ACCOUNT_WIDGET_H

#include <QtGui/QWidget>

class QTableWidget;
class QPushButton;
class QLineEdit;
class QLabel;

/**
 *  @class  SELUserAccountWidget
 */
class SELUserAccountWidget : public QWidget {
private:
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
    static const int ROWS_PER_PAGE;
    ///
    static const int NUM_COLUMNS;

public:
    ///
    SELUserAccountWidget(QWidget * parent = 0);
    ///
    virtual ~SELUserAccountWidget();
};

#endif /// Not SEL_USER_ACCOUNT_WIDGET_H
