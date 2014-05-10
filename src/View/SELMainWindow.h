#ifndef SEL_MAIN_WINDOW_H
#define SEL_MAIN_WINDOW_H

#include <QtGui/QMainWindow>

class SELMainWidget;
class SELController;

/**
 *  @class  SELMainWindow
 */
class SELMainWindow : public QMainWindow {
Q_OBJECT

private:
    ///
    SELController & controller;
    ///
    SELMainWidget * mainWidget;

public:
    ///
    SELMainWindow(SELController & controller);
    ///
    virtual ~SELMainWindow();
};

#endif /// Not SEL_MAIN_WINDOW_H
