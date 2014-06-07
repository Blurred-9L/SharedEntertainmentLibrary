#include "SELUserLoansWidget.h"
#include "../Controller/SELController.h"
#include "../Model/Loan.h"
#include "../Model/LoanRequest.h"
#include "../Model/Error.h"

#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

const unsigned SELUserLoansWidget::ITEMS_PER_PAGE = 15;

SELUserLoansWidget::SELUserLoansWidget(SELController & controller, QWidget * parent) :
    QWidget(parent), controller(controller), loanIds(0), requestIds(0)
{
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    QVBoxLayout * loansLayout = new QVBoxLayout();
    QVBoxLayout * requestsLayout = new QVBoxLayout();
    QHBoxLayout * loansButtonLayout = new QHBoxLayout();
    QHBoxLayout * requestsButtonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(loansLayout);
    mainLayout->addLayout(requestsLayout);
    
    loansLabel = new QLabel("Loans:");
    loansLayout->addWidget(loansLabel);
    
    loansListWidget = new QListWidget();
    loanIds = new unsigned long long[ITEMS_PER_PAGE];
    for (unsigned i = 0; i < ITEMS_PER_PAGE; i++) {
        loanIds[i] = 0;
    }
    loansLayout->addWidget(loansListWidget);
    
    loansLayout->addLayout(loansButtonLayout);
    
    loansPrevButton = new QPushButton("Previous");
    loansButtonLayout->addWidget(loansPrevButton);
    
    curLoanPageLabel = new QLabel();
    curLoanPageLabel->setNum(1);
    curLoanPageLabel->setAlignment(Qt::AlignCenter);
    loansButtonLayout->addWidget(curLoanPageLabel);
    
    loansNextButton = new QPushButton("Next");
    loansButtonLayout->addWidget(loansNextButton);
    
    requestsLabel = new QLabel("Requests:");
    requestsLayout->addWidget(requestsLabel);
    
    requestsListWidget = new QListWidget();
    requestIds = new unsigned long long[ITEMS_PER_PAGE];
    for (unsigned i = 0; i < ITEMS_PER_PAGE; i++) {
        requestIds[i] = 0;
    }
    requestsLayout->addWidget(requestsListWidget);
    
    requestsLayout->addLayout(requestsButtonLayout);
    
    requestsPrevButton = new QPushButton("Previous");
    requestsButtonLayout->addWidget(requestsPrevButton);
    
    curRequestPageLabel = new QLabel();
    curRequestPageLabel->setNum(1);
    curRequestPageLabel->setAlignment(Qt::AlignCenter);
    requestsButtonLayout->addWidget(curRequestPageLabel);
    
    requestsNextButton = new QPushButton("Next");
    requestsButtonLayout->addWidget(requestsNextButton);
    
    /// Signals needed...
    /// Click previous loan button, load previous loans page.
    connect(loansPrevButton, SIGNAL(clicked()),
            this, SLOT(updateLoansPagePrev()));
    /// Click next loan button, load next loan page.
    connect(loansNextButton, SIGNAL(clicked()),
            this, SLOT(updateLoansPageNext()));
    /// Click previous request button, load previous requests page.
    connect(requestsPrevButton, SIGNAL(clicked()),
            this, SLOT(updateRequestsPagePrev()));
    /// Click next request button, load next requests page.
    connect(requestsNextButton, SIGNAL(clicked()),
            this, SLOT(updateRequestsPageNext()));
}

SELUserLoansWidget::~SELUserLoansWidget()
{
    if (loanIds != 0) {
        delete [] loanIds;
    }
    if (requestIds != 0) {
        delete [] requestIds;
    }
}

void SELUserLoansWidget::loadFirstLoanPage()
{
    Loan * loans = 0;
    int numLoans = 0;
    
    loans = controller.retrieveLoanPage(1, numLoans);
    if (loans != 0) {
        updateLoansPage(loans, (unsigned)numLoans);
    }
}

void SELUserLoansWidget::reloadLoanPage()
{
    Loan * loans = 0;
    int numLoans = 0;
    int curPage;
    
    curPage = curLoanPageLabel->text().toInt();
    loans = controller.retrieveLoanPage(curPage, numLoans);
    if (loans != 0) {
        updateLoansPage(loans, (unsigned)numLoans);
    } else {
        Error::raiseError(Error::ERROR_PAGE_RELOAD_FAIL);
    }
}

void SELUserLoansWidget::updateLoansPage(Loan * loans, unsigned numLoans)
{
    QList<QListWidgetItem *> listItems = loansListWidget->findItems("*", Qt::MatchWildcard);
    QListWidgetItem * removedItem = 0;
    unsigned i, size = listItems.size(), indexOffset;
    
    for (i = 0; i < numLoans; i++) {
        if (i >= size) {
            loansListWidget->addItem(new QListWidgetItem());
        }
        loansListWidget->item(i)->setText(loans[i].toString().c_str());
        loanIds[i] = loans[i].getId();
    }
    
    /// If less loans were obtained than there previously were:
    indexOffset = 0;
    while (i < size) {
        removedItem = loansListWidget->takeItem(i - indexOffset);
        if (removedItem != 0) {
            delete removedItem;
            removedItem = 0;
        }
        loanIds[i] = 0;
        i++;
        indexOffset++;
    }
    
    delete [] loans;
}

void SELUserLoansWidget::updateRequestsPage(LoanRequest * requests, unsigned numRequests)
{
    QList<QListWidgetItem *> listItems = requestsListWidget->findItems("*", Qt::MatchWildcard);
    QListWidgetItem * removedItem = 0;
    unsigned i, size = listItems.size(), indexOffset;
    
    for (i = 0; i < numRequests; i++) {
        if (i >= size) {
            requestsListWidget->addItem(new QListWidgetItem());
        }
        requestsListWidget->item(i)->setText(requests[i].toString().c_str());
        requestIds[i] = requests[i].getId();
    }
    
    /// If less requests were obtained than there previously were:
    indexOffset = 0;
    while (i < size) {
        removedItem = requestsListWidget->takeItem(i - indexOffset);
        if (removedItem != 0) {
            delete removedItem;
            removedItem = 0;
        }
        requestIds[i] = 0;
        i++;
        indexOffset++;
    }
    
    delete [] requests;
}

/////////////
// Private //
/////////////

void SELUserLoansWidget::updateLoansPageNext()
{
    Loan * loans = 0;
    int pageToGet;
    int numLoans = 0;
    bool ok;
    
    pageToGet = curLoanPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet++;
        loans = controller.retrieveLoanPage(pageToGet, numLoans);
        if ((loans != 0) && (numLoans > 0)) {
            curLoanPageLabel->setNum(pageToGet);
            updateLoansPage(loans, (unsigned)numLoans);
        }
    } else {
        Error::raiseError(Error::ERROR_NO_SUCH_PAGE_LOAN);
    }
}

void SELUserLoansWidget::updateLoansPagePrev()
{
    int pageToGet;
    bool ok;
    
    pageToGet = curLoanPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet--;
        if (pageToGet > 0) {
            emit getUserLoansPage(pageToGet);
            curLoanPageLabel->setNum(pageToGet);
        }
    } else {
        Error::raiseError(Error::ERROR_NO_SUCH_PAGE_LOAN);
    }
}

void SELUserLoansWidget::updateRequestsPageNext()
{
    int pageToGet;
    bool ok;
    
    pageToGet = curRequestPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet++;
        emit getUserRequestsPage(pageToGet);
        curRequestPageLabel->setNum(pageToGet);
    } else {
        Error::raiseError(Error::ERROR_NO_SUCH_PAGE_REQ);
    }
}

void SELUserLoansWidget::updateRequestsPagePrev()
{
    int pageToGet;
    bool ok;
    
    pageToGet = curRequestPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet--;
        if (pageToGet > 0) {
            emit getUserRequestsPage(pageToGet);
            curRequestPageLabel->setNum(pageToGet);
        }
    } else {
        Error::raiseError(Error::ERROR_NO_SUCH_PAGE_REQ);
    }
}
