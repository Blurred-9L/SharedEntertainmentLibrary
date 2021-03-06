#include "./Controller/SELController.h"
#include "./View/SELMainWindow.h"
#include "./View/SELLoginDialog.h"
#include "./DB/DBConnection.h"

#include <QtGui/QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELController controller;
    SELMainWindow window(controller);
    SELLoginDialog loginDialog(controller);
    
    /**
    - Instantiate the login dialog.
    - Show the login dialog.
    - Obtain results of login from login dialog
    - If login successful -> proceed.
    - Else -> exit
    */
    
    window.setAttribute(Qt::WA_QuitOnClose);
    loginDialog.show();
    
    QObject::connect(&loginDialog, SIGNAL(loginSuccessful()),
                     &window, SLOT(show()));
    QObject::connect(&loginDialog, SIGNAL(loginSuccessful()),
                     &window, SIGNAL(idAvailable()));
    
    app.exec();
    
    DBConnection::deleteInstance();
    
    return 0;
}
