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
    unsigned long long requestId;
    ///
    bool replySent;
    ///
    unsigned long long requestStatus;
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
    unsigned long long getRequestId() const;
    ///
    bool getReplySent() const;
    ///
    unsigned long long getRequestStatus() const;
    ///
    const string & getMessage() const;
    ///
    void setRequestId(unsigned long long requestId);
    ///
    void setReplySent(bool replySent);
    ///
    void setRequestStatus(unsigned long long requestStatus);
    ///
    void setMessage(const string & message);
    ///
    string toString() const;
    
    ///
    static string getRequestStatusString(unsigned long long requestStatus);
};

#endif /// Not LOAN_REQUEST_H
