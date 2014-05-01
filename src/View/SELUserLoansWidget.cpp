#include "SELUserLoansWidget.h"

#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

const unsigned SELUserLoansWidget::ITEMS_PER_PAGE = 15;

SELUserLoansWidget::SELUserLoansWidget(QWidget * parent) :
    QWidget(parent), loanIds(0), requestIds(0)
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
    /// Click previous loan button -> load previous loans page.
    /// Click next loan button -> load next loan page.
    /// Click previous request button -> load previous requests page.
    /// Click next request button -> load next requests page.
    /// Double click item -> 
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
