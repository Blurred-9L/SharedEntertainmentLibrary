#include "LoanModel.h"
#include "../DB/DBConnection.h"
#include "../DB/QueryResult.h"
#include "Loan.h"
#include "LoanRequest.h"
#include "Error.h"

#include <sstream>
using std::stringstream;

const int LoanModel::STATUS_INACTIVE = 1;
const int LoanModel::STATUS_UNAVAILABLE = 4;

LoanModel::LoanModel() :
    dbCon(DBConnection::getInstance())
{
}

LoanModel::~LoanModel()
{
}

Loan * LoanModel::getLastLoan(unsigned long long ownedItemId)
{
    Loan * loan = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    stringstream interval(stringstream::in | stringstream::out);
    int days;
    
    stream << "SELECT Loan.id AS loan_id, requestee_id, owned_item_id, "
              "start_data, duration, Loan_Status.status "
              "FROM Loan "
              "JOIN Owned_Item ON Owned_Item.id = owned_item_id "
              "JOIN Loan_Status ON Loan.status = Loan_Status.id "
              "WHERE owned_item_id = " << ownedItemId << " "
              "AND status < 4 "
              "ORDER BY start_data ASC;";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->last()) {
            loan = new Loan();
            loan->setId(result->value(0).toULongLong());
            loan->setStartDate(result->value(3).toDate());
            
            interval << result->value(4).toString().toAscii().data();
            interval >> days;
            loan->setDuration(QDateTime(loan->getStartDate().addDays(days)));
        }
        delete result;
    }
    
    return loan;
}

bool LoanModel::registerLoan(unsigned long long requesteeId, unsigned long long ownedItemId,
                             const QDate & startDate, const QDateTime & duration, int status)
{
    bool insertOk = false;
    stringstream stream(stringstream::out);
    
    stream << "INSERT INTO Loan (requestee_id, owned_item_id, start_data, "
              "duration, status) VALUES (" << requesteeId << ", "
           << ownedItemId << ", DATE \'" << startDate.year() << "-"
           << startDate.month() << "-" << startDate.day() << "\', "
           << "INTERVAL \'" << QDateTime(startDate).daysTo(duration)
           << " days\', " << status << ");";
           
    insertOk = dbCon.nonQuery(stream.str());
        
    return insertOk;
}

bool LoanModel::updateLoanStatuses()
{
    bool updateStartedOk = false;
    bool updateEndedOk = false;
    stringstream stream(stringstream::out);
    
    stream << "UPDATE Loan SET status = 2 WHERE start_data <= NOW() "
              "AND status = 1;";
    updateStartedOk = dbCon.nonQuery(stream.str());
    
    stream.seekp(stream.beg);
    stream << "UPDATE Loan SET status = 3 WHERE "
              "start_data + duration < NOW() AND status = 2;";
    updateEndedOk = dbCon.nonQuery(stream.str());
    
    return (updateStartedOk && updateEndedOk);
}

bool LoanModel::loanExists(unsigned long long requesteeId, unsigned long long ownedItemId)
{
    bool exists = false;
    QueryResult * result;
    stringstream stream(stringstream::out);
    
    stream << "SELECT Loan.id requestee_id, Loan.owned_item_id, start_data, "
              "duration, status FROM Loan "
              "JOIN Member ON requestee_id = Member.id "
              "JOIN Owned_Item on Owned_Item.id = owned_item_id "
              "WHERE requestee_id = " << requesteeId << " "
              "AND owned_item_id = " << ownedItemId << " "
              "AND status = 2;";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->size() > 0) {
            exists = true;
        }
        delete result;
    }
    
    return exists;
}

unsigned long long LoanModel::getLastLoanId()
{
    unsigned long long id = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT last_value from Loan_id_seq;";
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            id = result->value(0).toULongLong();
        }
        delete result;
    }
    
    
    return id;
}

bool LoanModel::registerLoanRequest(LoanRequest & request, unsigned long long loanId)
{
    bool insertOk = false;
    stringstream stream(stringstream::out);
    
    stream << "INSERT INTO Loan_Request (reply_status, request_status, "
              "message, loan_id) VALUES (1, FALSE, \'" << request.getMessage() <<
              "\', " << loanId << ");";
    insertOk = dbCon.nonQuery(stream.str()); 
    
    return insertOk;
}

