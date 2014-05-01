#ifndef SEL_USER_LOANS_WIDGET_H
#define SEL_USER_LOANS_WIDGET_H

#include <QtGui/QWidget>

class QListWidget;
class QPushButton;
class QLabel;

/**
 *  @class  SELUserLoansWidget
 */
class SELUserLoansWidget : public QWidget {
private:
    ///
    QListWidget * loansListWidget;
    ///
    QListWidget * requestsListWidget;
    ///
    QLabel * loansLabel;
    ///
    QLabel * requestsLabel;
    ///
    QLabel * curLoanPageLabel;
    ///
    QLabel * curRequestPageLabel;
    ///
    QPushButton * loansNextButton;
    ///
    QPushButton * loansPrevButton;
    ///
    QPushButton * requestsNextButton;
    ///
    QPushButton * requestsPrevButton;
    ///
    unsigned long long * loanIds;
    ///
    unsigned long long * requestIds;
    
    ///
    static const unsigned ITEMS_PER_PAGE;

public:
    ///
    SELUserLoansWidget(QWidget * parent = 0);
    ///
    virtual ~SELUserLoansWidget();
};

#endif /// Not SEL_USER_LOANS_WIDGET_H
