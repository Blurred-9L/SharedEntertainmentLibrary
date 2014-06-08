#include "SELMainWidget.h"
#include "SELMainLibraryWidget.h"
#include "SELUserLibraryWidget.h"
#include "SELUserLoansWidget.h"
#include "SELUserAccountWidget.h"
#include "../Controller/SELController.h"

SELMainWidget::SELMainWidget(SELController & controller, QWidget * parent) :
    QTabWidget(parent), controller(controller)
{
    mainLibraryWidget = new SELMainLibraryWidget(this->controller);
    userLibraryWidget = new SELUserLibraryWidget(this->controller);
    userAccountWidget = new SELUserAccountWidget(this->controller);
    userLoansWidget = new SELUserLoansWidget(this->controller);
    
    this->addTab(mainLibraryWidget, "Main library");
    this->addTab(userLibraryWidget, "User library");
    this->addTab(userLoansWidget, "Loans");
    this->addTab(userAccountWidget, "Account");
    this->setCurrentIndex(0);
    
    /// Connect signals here...
    connect(this, SIGNAL(notifyIdAvailable()),
            userLibraryWidget, SLOT(loadFirstPage()));
    ///
    connect(this, SIGNAL(notifyIdAvailable()),
            userLoansWidget, SLOT(loadFirstLoanPage()));
    ///
    connect(this, SIGNAL(notifyIdAvailable()),
            userLoansWidget, SLOT(loadFirstRequestPage()));
    ///
    connect(this, SIGNAL(notifyIdAvailable()),
            userAccountWidget, SLOT(loadUserData()));
    ///
    connect(this, SIGNAL(notifyIdAvailable()),
            userAccountWidget, SLOT(loadFirstMessagePage()));
    ///
    connect(this, SIGNAL(currentChanged(int)),
            this, SLOT(updateIfNecessary(int)));
}

SELMainWidget::~SELMainWidget()
{
}

void SELMainWidget::updateIfNecessary(int index)
{
    switch (index) {
    case 0:
        break;
    case 1:
        if (mainLibraryWidget->checkUserLibraryChanged()) {
            userLibraryWidget->reloadPage();
            mainLibraryWidget->setUserLibraryChanged(false);
        }
        break;
    case 2:
        if (mainLibraryWidget->checkUserRequestsChanged()) {
            userLoansWidget->reloadRequestPage();
            mainLibraryWidget->setUserRequestsChanged(false);
        }
        if (userAccountWidget->checkUserLoansChanged()) {
            userLoansWidget->reloadLoanPage();
            userAccountWidget->setUserLoansChanged(false);
        }
        break;
    case 3:
        break;
    }
}
