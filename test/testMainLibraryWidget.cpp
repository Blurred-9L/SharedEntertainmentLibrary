#include <QtGui/QApplication>
#include "../src/View/SELMainLibraryWidget.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    SELMainLibraryWidget window;
    
    window.setAttribute(Qt::WA_QuitOnClose);
    window.show();
    
    app.exec();
    
    return 0;
}
