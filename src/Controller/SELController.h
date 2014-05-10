#ifndef SEL_CONTROLLER_H
#define SEL_CONTROLLER_H

#include <string>
using std::string;

#include <QtCore/QObject>

class LoginModel;
class ItemModel;
class EntertainmentItem;

class SELController : public QObject {
Q_OBJECT

private:
    ///
    unsigned long long activeUserId;
    ///
    LoginModel * loginModel;
    ///
    ItemModel * itemModel;
    
public:
    ///
    SELController(QObject * parent = 0);
    ///
    virtual ~SELController();
    
public slots:
    ///
    bool memberLogIn(const string & username, const string & password);
    ///
    EntertainmentItem * retrieveLibraryPage(int pageToGet, int & numItems);
    ///
    EntertainmentItem * retrieveItem(unsigned long long id, unsigned long long & type);
};

#endif /// Not SEL_CONTROLLER_H
