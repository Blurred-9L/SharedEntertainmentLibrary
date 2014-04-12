#ifndef LOAN_REQUEST_H
#define LOAN_REQUEST_H

#include "Loan.h"

#include <string>
using std::string;

class Member;
class OwnedItem;

class LoanRequest : public Loan {
private:
    ///
    bool replySent;
    ///
    unsigned requestStatus;
    ///
    string message;
    
public:
    /**
     *  @enum   RequestStatus
     */
    enum RequestStatus {
        STATUS_UNKNOWN = 0
    };
    
    ///
    LoanRequest();
    ///
    LoanRequest(Member * requestingMember, OwnedItem * requestedItem,
                const QDate & startDate, const QDateTime & duration,
                const string & message);
    ///
    virtual ~LoanRequest();
    ///
    bool getReplySent() const;
    ///
    unsigned getRequestStatus() const;
    ///
    const string & getMessage() const;
    ///
    void setReplySent(bool replySent);
    ///
    void setRequestStatus(unsigned requestStatus);
    ///
    void setMessage(const string & message);
};

#endif /// Not LOAN_REQUEST_H
