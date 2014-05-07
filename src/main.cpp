#include "./View/SELMainWindow.h"
#include "./View/SELLoginDialog.h"
#include "./DB/DBConnection.h"

#include <QtGui/QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELMainWindow window;
    SELLoginDialog loginDialog;
    
    /**
    - Instantiate the login dialog.
    - Show the login dialog.
    - Obtain results of login from login dialog
    - If login successful -> proceed.
    - Else -> exit
    */
    
    window.setAttribute(Qt::WA_QuitOnClose);
    loginDialog.show();
    
    QObject::connect(&loginDialog, SIGNAL(loginSuccessful(long long int)),
                     &window, SLOT(receiveUserId(long long int)));
    
    app.exec();
    
    DBConnection::deleteInstance();
    
    return 0;
}
