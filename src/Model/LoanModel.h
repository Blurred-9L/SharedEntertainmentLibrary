#ifndef LOAN_MODEL_H
#define LOAN_MODEL_H

#include <string>
using std::string;

class DBConnection;
class Loan;
class LoanRequest;

class QDate;
class QDateTime;

const int DEFAULT_LOAN_DURATION = 14;

class LoanModel {
private:
    ///
    DBConnection & dbCon;

public:
    ///
    static const int STATUS_INACTIVE;
    ///
    static const int STATUS_UNAVAILABLE;

    ///
    LoanModel();
    ///
    virtual ~LoanModel();
    ///
    Loan * getLastLoan(unsigned long long ownedItemId);
    ///
    bool registerLoan(unsigned long long requesteeId, unsigned long long ownedItemId,
                      const QDate & startDate, const QDateTime & duration, int status);
    ///
    bool updateLoanStatuses();
    ///
    bool loanExists(unsigned long long requesteeId, unsigned long long ownedItemId);
    ///
    bool loanPossible(const QDate & startDate, const QDate & endDate, unsigned long long ownedItemId);
    ///
    unsigned long long getLastLoanId();
    ///
    bool registerLoanRequest(LoanRequest & request, unsigned long long loanId);
    ///
    Loan * getUserLoansOnPage(unsigned long long userId, int pageNumber, int & numLoans);
    ///
    LoanRequest * getRequestsOfUserPage(unsigned long long userId, int pageNumber, int & numRequests);
    ///
    LoanRequest * getUserMessagesPage(unsigned long long userId, int pageNumber, int & numRequests);
    ///
    string * getRequestMessage(unsigned long long requestId);
    ///
    LoanRequest * getLoanRequest(unsigned long long requestId);
    ///
    bool rejectLoanRequest(unsigned long long requestId);
    ///
    bool acceptLoanRequest(unsigned long long requestId);
};

#endif /// Not LOAN_MODEL_h
