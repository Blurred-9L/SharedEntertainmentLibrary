#ifndef SEL_MAIN_WINDOW_H
#define SEL_MAIN_WINDOW_H

#include <QtGui/QMainWindow>

class SELMainWidget;

/**
 *  @class  SELMainWindow
 */
class SELMainWindow : public QMainWindow {
Q_OBJECT

private:
    ///
    SELMainWidget * mainWidget;

public:
    ///
    SELMainWindow();
    ///
    virtual ~SELMainWindow();
    
public slots:
    ///
    void receiveUserId(long long int userId);
};

#endif /// Not SEL_MAIN_WINDOW_H
