#include "../src/View/SELUserAccountWidget.h"
#include <QtGui/QApplication>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELUserAccountWidget window;
    
    window.setAttribute(Qt::WA_QuitOnClose);
    window.show();
    
    app.exec();
    
    return 0;
}
