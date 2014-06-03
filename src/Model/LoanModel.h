#ifndef LOAN_MODEL_H
#define LOAN_MODEL_H

class DBConnection;
class Loan;

class QDate;
class QDateTime;

const int DEFAULT_LOAN_DURATION = 14;

class LoanModel {
private:
    ///
    DBConnection & dbCon;

public:
    ///
    LoanModel();
    ///
    virtual ~LoanModel();
    ///
    Loan * getLastLoan(unsigned long long ownedItemId);
    ///
    bool registerLoan(unsigned long long requesteeId, unsigned long long ownedItemId,
                      const QDate & startDate, const QDateTime & duration);
    ///
    bool updateLoanStatuses();
    ///
    bool loanExists(unsigned long long requesteeId, unsigned long long ownedItemId);
};

#endif /// Not LOAN_MODEL_h
