#ifndef SEL_CONTROLLER_H
#define SEL_CONTROLLER_H

#include <string>
using std::string;

#include <QtCore/QObject>

class LoginModel;

class SELController : public QObject {
Q_OBJECT

private:
    ///
    unsigned long long activeUserId;
    ///
    LoginModel * loginModel;
    
public:
    ///
    SELController(QObject * parent = 0);
    ///
    virtual ~SELController();
    
public slots:
    ///
    bool memberLogIn(const string & username, const string & password);
};

#endif /// Not SEL_CONTROLLER_H
