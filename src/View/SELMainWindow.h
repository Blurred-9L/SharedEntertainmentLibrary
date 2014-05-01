#ifndef SEL_MAIN_WINDOW_H
#define SEL_MAIN_WINDOW_H

#include <QtGui/QMainWindow>

class SELMainWidget;

/**
 *  @class  SELMainWindow
 */
class SELMainWindow : public QMainWindow {
private:
    ///
    SELMainWidget * mainWidget;

public:
    ///
    SELMainWindow();
    ///
    virtual ~SELMainWindow();
};

#endif /// Not SEL_MAIN_WINDOW_H
