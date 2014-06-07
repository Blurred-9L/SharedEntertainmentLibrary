#ifndef LOAN_H
#define LOAN_H

#include <QtCore/QDate>
#include <QtCore/QDateTime>

#include <string>
using std::string;

class Member;
class OwnedItem;

/**
 *  @class  Loan
 */
class Loan {
private:
    ///
    unsigned long long id;
    ///
    Member * requestingMember;
    ///
    OwnedItem * requestedItem;
    ///
    QDate startDate;
    ///
    QDateTime duration;
    ///
    unsigned long long status;
    
public:
    /**
     *  @enum   LoanStatus
     */
    enum LoanStatus {
        LOAN_STATUS_INVALID = 0,
        LOAN_STATUS_INACTIVE,
        LOAN_STATUS_ACTIVE,
        LOAN_STATUS_ENDED,
        LOAN_STATUS_NOT_AVAILABLE,
        LOAN_STATUS_IMPOSSIBLE
    };

    ///
    Loan();
    ///
    Loan(Member * requestingMember, OwnedItem * requestedItem,
         const QDate & startDate, const QDateTime & duration);
    ///
    virtual ~Loan();
    ///
    unsigned long long getId() const;
    ///
    const Member & getRequestingMember() const;
    ///
    Member & getRequestingMember();
    ///
    const OwnedItem & getRequestedItem() const;
    ///
    OwnedItem & getRequestedItem();
    ///
    const QDate & getStartDate() const;
    ///
    QDate & getStartDate();
    ///
    const QDateTime & getDuration() const;
    ///
    QDateTime & getDuration();
    ///
    unsigned long long getStatus() const;
    ///
    void setId(unsigned long long id);
    ///
    void setRequestingMember(Member * requestingMember);
    ///
    void setRequestedItem(OwnedItem * requestedItem);
    ///
    void setStartDate(const QDate & startDate);
    ///
    void setDuration(const QDateTime & duration);
    ///
    void setStatus(unsigned long long status);
    ///
    string toString() const;
    ///
    QDate getEndingDate() const;
    
    static string getStatusString(unsigned long long status);
};

#endif /// Not LOAN_H
