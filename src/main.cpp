#include "./View/SELMainWindow.h"

#include <QtGui/QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELMainWindow window;
    
    /**
    - Instantiate the login dialog.
    - Show the login dialog.
    - Obtain results of login from login dialog
    - If login successful -> proceed.
    - Else -> exit
    */
    
    window.setAttribute(Qt::WA_QuitOnClose);
    window.show();
    
    app.exec();
    
    return 0;
}
