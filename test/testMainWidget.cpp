#include "../src/View/SELMainWidget.h"
#include <QtGui/QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELMainWidget window;
    
    window.setAttribute(Qt::WA_QuitOnClose);
    window.show();
    
    app.exec();

    return 0;
}
