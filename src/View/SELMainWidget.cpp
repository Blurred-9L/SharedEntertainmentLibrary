#include "SELMainWidget.h"
#include "SELMainLibraryWidget.h"
#include "SELUserLibraryWidget.h"
#include "SELUserLoansWidget.h"
#include "SELUserAccountWidget.h"

SELMainWidget::SELMainWidget(QWidget * parent) :
    QTabWidget(parent)
{
    mainLibraryWidget = new SELMainLibraryWidget();
    userLibraryWidget = new SELUserLibraryWidget();
    userAccountWidget = new SELUserAccountWidget();
    userLoansWidget = new SELUserLoansWidget();
    
    this->addTab(mainLibraryWidget, "Main library");
    this->addTab(userLibraryWidget, "User library");
    this->addTab(userLoansWidget, "Loans");
    this->addTab(userAccountWidget, "Account");
    this->setCurrentIndex(0);
    
    /// Connect signals here...
}

SELMainWidget::~SELMainWidget()
{
}
