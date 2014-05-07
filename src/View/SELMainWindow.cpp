#include "SELMainWindow.h"
#include "SELMainWidget.h"

SELMainWindow::SELMainWindow() :
    QMainWindow()
{
    mainWidget = new SELMainWidget();
    
    this->setCentralWidget(mainWidget);
    this->setWindowTitle("Shared Entertainment Library");
}

SELMainWindow::~SELMainWindow()
{
}

void SELMainWindow::receiveUserId(long long int userId)
{
    this->show();
}
