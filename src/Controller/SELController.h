#ifndef SEL_CONTROLLER_H
#define SEL_CONTROLLER_H

#include <string>
using std::string;

#include <QtCore/QObject>

class LoginModel;
class ItemModel;
class EntertainmentItem;
class OwnedItem;

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
    ///
    OwnedItem * retrieveUserLibraryPage(int pageToGet, int & numItems);
    ///
    unsigned long long retrieveItemId(unsigned long long ownedItemId);
    ///
    unsigned long long retrieveItemPolicy(unsigned long long ownedItemId);
    ///
    bool changeItemPolicy(unsigned long long ownedItemId, int policy);
};

#endif /// Not SEL_CONTROLLER_H
