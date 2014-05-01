#include "../src/View/SELUserLoansWidget.h"
#include <QtGui/QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELUserLoansWidget window;
    
    window.setAttribute(Qt::WA_QuitOnClose);
    window.show();
    
    app.exec();
    
    return 0;    
}
