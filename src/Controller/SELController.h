#ifndef SEL_CONTROLLER_H
#define SEL_CONTROLLER_H

#include <string>
using std::string;

#include <QtCore/QObject>

class LoginModel;
class ItemModel;
class MemberModel;
class LoanModel;
class EntertainmentItem;
class OwnedItem;
class Member;

class QDate;

class SELController : public QObject {
Q_OBJECT

private:
    ///
    unsigned long long activeUserId;
    ///
    LoginModel * loginModel;
    ///
    ItemModel * itemModel;
    ///
    MemberModel * memberModel;
    ///
    LoanModel * loanModel;
    
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
    ///
    Member * retrieveData();
    ///
    bool checkUserOwnsItem(unsigned long long itemId);
    ///
    bool addItemToUserLibrary(unsigned long long itemId);
    ///
    OwnedItem * retrieveOwners(unsigned long long itemId, int & numItems);
    ///
    bool scheduleAutomaticLoan(OwnedItem & item);
    ///
    bool checkIfActiveLoan(unsigned long long ownedItemId);
    ///
    bool processLoanRequest(OwnedItem & item, const string & message,
                            const QDate & date, int daysOnLoan);
};

#endif /// Not SEL_CONTROLLER_H
