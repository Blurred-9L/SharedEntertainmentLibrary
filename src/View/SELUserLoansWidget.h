#ifndef SEL_USER_LOANS_WIDGET_H
#define SEL_USER_LOANS_WIDGET_H

#include <QtGui/QWidget>

class QListWidget;
class QPushButton;
class QLabel;

class SELController;
class Loan;
class LoanRequest;

/**
 *  @class  SELUserLoansWidget
 */
class SELUserLoansWidget : public QWidget {
Q_OBJECT

private:
    ///
    SELController & controller;
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

public:
    ///
    static const unsigned ITEMS_PER_PAGE;

    ///
    SELUserLoansWidget(SELController & controller, QWidget * parent = 0);
    ///
    virtual ~SELUserLoansWidget();
    
public slots:
    ///
    void updateLoansPage(Loan * loans, unsigned numLoans);
    ///
    void updateRequestsPage(LoanRequest * requests, unsigned numRequests);
    ///
    void loadFirstLoanPage();
    ///
    void reloadLoanPage();
    
private slots:
    ///
    void updateLoansPageNext();
    ///
    void updateLoansPagePrev();
    ///
    void updateRequestsPageNext();
    ///
    void updateRequestsPagePrev();

signals:
    ///
    void getUserLoansPage(int page);
    ///
    void getUserRequestsPage(int page);
};

#endif /// Not SEL_USER_LOANS_WIDGET_H
