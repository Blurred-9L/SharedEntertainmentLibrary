#ifndef LOAN_H
#define LOAN_H

#include <QtCore/QDate>
#include <QtCore/QDateTime>

class Member;
class OwnedItem;

/**
 *  @class  Loan
 */
class Loan {
private:
    ///
    Member * requestingMember;
    ///
    OwnedItem * requestedItem;
    ///
    QDate startDate;
    ///
    QDateTime duration;
    
public:
    ///
    Loan();
    ///
    Loan(Member * requestingMember, OwnedItem * requestedItem,
         const QDate & startDate, const QDateTime & duration);
    ///
    virtual ~Loan();
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
    void setRequestingMember(Member * requestingMember);
    ///
    void setRequestedItem(OwnedItem * requestedItem);
    ///
    void setStartDate(const QDate & startDate);
    ///
    void setDuration(const QDateTime & duration);
};

#endif /// Not LOAN_H
