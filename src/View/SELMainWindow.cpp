#include "SELMainWindow.h"
#include "SELMainWidget.h"

SELMainWindow::SELMainWindow(SELController & controller) :
    QMainWindow(), controller(controller)
{
    mainWidget = new SELMainWidget(this->controller);
    
    this->setCentralWidget(mainWidget);
    this->setWindowTitle("Shared Entertainment Library");
    this->resize(650, 400);
    
    connect(this, SIGNAL(idAvailable()), mainWidget, SIGNAL(notifyIdAvailable()));
}

SELMainWindow::~SELMainWindow()
{
}

