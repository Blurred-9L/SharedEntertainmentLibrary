#ifndef LOAN_MODEL_H
#define LOAN_MODEL_H

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
    unsigned long long getLastLoanId();
    ///
    bool registerLoanRequest(LoanRequest & request, unsigned long long loanId);
    ///
    Loan * getUserLoansOnPage(unsigned long long userId, int pageNumber, int & numLoans);
};

#endif /// Not LOAN_MODEL_h
