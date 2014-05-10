#ifndef SEL_MAIN_WIDGET_H
#define SEL_MAIN_WIDGET_H

#include <QtGui/QTabWidget>

class SELController;
class SELMainLibraryWidget;
class SELUserLibraryWidget;
class SELUserAccountWidget;
class SELUserLoansWidget;

/**
 *  @class  SELMainWidget
 */
class SELMainWidget : public QTabWidget {
private:
    ///
    SELController & controller;
    ///
    SELMainLibraryWidget * mainLibraryWidget;
    ///
    SELUserLibraryWidget * userLibraryWidget;
    ///
    SELUserAccountWidget * userAccountWidget;
    ///
    SELUserLoansWidget * userLoansWidget;
    
public:
    ///
    SELMainWidget(SELController & controller, QWidget * parent = 0);
    ///
    virtual ~SELMainWidget();
};

#endif /// Not SEL_MAIN_WIDGET_H
