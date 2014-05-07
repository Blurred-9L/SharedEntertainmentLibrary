#ifndef SEL_MAIN_WIDGET_H
#define SEL_MAIN_WIDGET_H

#include <QtGui/QTabWidget>

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
    SELMainLibraryWidget * mainLibraryWidget;
    ///
    SELUserLibraryWidget * userLibraryWidget;
    ///
    SELUserAccountWidget * userAccountWidget;
    ///
    SELUserLoansWidget * userLoansWidget;
    ///
    unsigned long long userId;
    
public:
    ///
    SELMainWidget(QWidget * parent = 0);
    ///
    virtual ~SELMainWidget();
    ///
    unsigned long long getUserId() const;
    ///
    void setUserId(unsigned long long userId);
};

#endif /// Not SEL_MAIN_WIDGET_H
