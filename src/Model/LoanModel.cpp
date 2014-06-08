#include "LoanModel.h"
#include "../DB/DBConnection.h"
#include "../DB/QueryResult.h"
#include "Loan.h"
#include "LoanRequest.h"
#include "Error.h"
#include "Member.h"
#include "OwnedItem.h"

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
              "AND Loan.status < 4 "
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
    bool updateRequestOk = false;
    bool updateNotAnsweredOk = false;
    stringstream stream(stringstream::out);
    
    stream << "UPDATE Loan SET status = 2 WHERE start_data <= NOW() "
              "AND status = 1;";
    updateStartedOk = dbCon.nonQuery(stream.str());
    
    stream.seekp(stream.beg);
    stream << "UPDATE Loan SET status = 3 WHERE "
              "start_data + duration < NOW() AND status = 2;";
    updateEndedOk = dbCon.nonQuery(stream.str());
    
    stream.seekp(stream.beg);
    stream << "UPDATE Loan_Request SET reply_status = 3, "
              "request_status = TRUE FROM Loan "
              "WHERE start_data >= NOW() AND status = 4 "
              "AND Loan.id = loan_id;";
    updateRequestOk = dbCon.nonQuery(stream.str());
    
    stream.seekp(stream.beg);
    stream << "UPDATE Loan SET status = 5 WHERE "
              "start_data >= NOW() AND status = 4;";
    updateNotAnsweredOk = dbCon.nonQuery(stream.str());
    
    return (updateStartedOk && updateEndedOk && updateRequestOk &&
            updateNotAnsweredOk);
}

bool LoanModel::loanExists(unsigned long long requesteeId, unsigned long long ownedItemId)
{
    bool exists = false;
    QueryResult * result;
    stringstream stream(stringstream::out);
    
    /// Checks if there is an active loan of the item at this current time.
    stream << "SELECT Loan.id, requestee_id, Loan.owned_item_id, start_data, "
              "duration, status FROM Loan "
              "JOIN Member ON requestee_id = Member.id "
              "JOIN Owned_Item on Owned_Item.id = owned_item_id "
              "WHERE requestee_id = " << requesteeId << " "
              "AND owned_item_id = " << ownedItemId << " "
              "AND status <= 2;";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->size() > 0) {
            exists = true;
        }
        delete result;
    }
    
    return exists;
}

bool LoanModel::loanPossible(const QDate & startDate, const QDate & endDate,
                             unsigned long long ownedItemId)
{
    bool ok = true;
    stringstream stream(stringstream::out);
    QueryResult * result = 0;
    QDate curDate(startDate);
    string date;
    
    while ((curDate <= endDate) && (ok)) {
        date = curDate.toString("yyyy-MM-dd").toAscii().data();
        stream.seekp(stream.beg);
        stream << "SELECT id, requestee_id, owned_item_id, start_data, "
                  "duration, status FROM Loan "
                  "WHERE owned_item_id = " << ownedItemId << " "
                  "AND (DATE \'" << date << "\' < start_data "
                  "OR DATE \'" << date << "\' > start_data + duration) "
                  "AND status <= 2;";
                  
        result = dbCon.query(stream.str());
        if (result != 0) {
            ok = (result->size() == 0);
            curDate = curDate.addDays(1);
            delete result;
        } else {
            ok = false;
        }
    }
    
    return ok;
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

Loan * LoanModel::getUserLoansOnPage(unsigned long long userId, int pageNumber, int & numLoans)
{
    Loan * loans = 0;
    Loan * loan;
    OwnedItem * ownedItem;
    Member * member;
    Member * owner;
    stringstream stream(stringstream::out);
    stringstream interval(stringstream::in | stringstream::out);
    QueryResult * result;
    unsigned index;
    unsigned offset = (pageNumber - 1) * 15;
    int days;
    
    stream << "SELECT Loan.id, requestee_id, owned_item_id, start_data, "
              "duration, Loan.status, Item.id AS e_item_id, title, "
              "Genre.genre, Publisher.publisher, year, Item.type, "
              "Owned_Item.policy, username, email, owner_id, "
              "owner_username, owner_email "
              "FROM Loan "
              "JOIN Loan_Status ON Loan.status = Loan_Status.id "
              "JOIN Owned_Item ON owned_item_id = Owned_Item.id "
              "JOIN Item ON Item.id = Owned_Item.item_id "
              "JOIN Publisher ON Publisher.id = Item.publisher "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Member ON requestee_id = Member.id "
              "JOIN "
                  "(SELECT Loan.id AS inner_loan_id, Member.id AS owner_id, "
                  "username AS owner_username, email AS owner_email "
                  "FROM Member "
                  "JOIN Owned_Item ON Member.id = Owned_Item.member_id "
                  "JOIN Loan ON Owned_Item.id = Loan.owned_item_id) "
              "AS Owner ON owner_id = Owned_Item.member_id "
              "AND inner_loan_id = Loan.id "
              "WHERE owner_id = " << userId << " "
              "AND Loan.status <= 3 "
              "ORDER BY start_data DESC, Loan.id ASC "
              "LIMIT 15 OFFSET " << offset << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        numLoans = result->size();
        if (numLoans > 0) {
            loans = new (std::nothrow) Loan[numLoans];
        }
        if (loans != 0) {
            index = 0;
            while (result->next()) {
                loan = &loans[index];
                /// Set loan's data.
                loan->setId(result->value(0).toULongLong());
                loan->setStartDate(result->value(3).toDate());
                
                interval.seekp(interval.beg);
                interval << result->value(4).toString().toAscii().data();
                interval.seekg(interval.beg);
                interval >> days;
                loan->setDuration(QDateTime(loan->getStartDate().addDays(days)));
                loan->setStatus(result->value(5).toULongLong());
                /// Set owned_item's data.
                ownedItem = new OwnedItem();
                ownedItem->setId(result->value(6).toULongLong());
                ownedItem->setTitle(result->value(7).toString().toAscii().data());
                ownedItem->setGenre(result->value(8).toString().toAscii().data());
                ownedItem->setPublisher(result->value(9).toString().toAscii().data());
                ownedItem->setYear(result->value(10).toUInt());
                ownedItem->setOwnedItemId(result->value(2).toULongLong());
                ownedItem->setItemType(result->value(11).toULongLong());
                ownedItem->setItemPolicy(result->value(12).toULongLong());
                loan->setRequestedItem(ownedItem);
                /// Set member's data.
                member = new Member();
                member->setId(result->value(1).toULongLong());
                member->setUsername(result->value(13).toString().toAscii().data());
                member->setEmail(result->value(14).toString().toAscii().data());
                loan->setRequestingMember(member);
                
                /// Set owner's data.
                owner = new Member();
                owner->setId(result->value(15).toULongLong());
                owner->setUsername(result->value(16).toString().toAscii().data());
                owner->setEmail(result->value(17).toString().toAscii().data());
                ownedItem->setOwner(owner);
                
                index++;
            }
        }
        delete result;
    }
    
    return loans;
}

LoanRequest * LoanModel::getRequestsOfUserPage(unsigned long long userId,
                                           int pageNumber, int & numRequests)
{
    LoanRequest * requests = 0;
    LoanRequest * request = 0;
    OwnedItem * item = 0;
    Member * member = 0;
    Member * owner = 0;
    stringstream stream(stringstream::out);
    stringstream interval(stringstream::in | stringstream::out);
    QueryResult * result;
    unsigned index;
    unsigned offset = (pageNumber - 1) * 15;
    int days;
    
    stream << "SELECT Loan_Request.id, reply_status, request_status, "
              "loan_id, requestee_id, owned_item_id, start_data, "
              "duration, Loan.status, Item.id AS e_item_id, title, "
              "Genre.genre, Publisher.publisher, year, Item.type, "
              "Owned_Item.policy, username, email, owner_id, "
              "owner_username, owner_email FROM Loan_Request "
              "JOIN Loan ON loan_id = Loan.id "
              "JOIN Owned_Item ON owned_item_id = Owned_Item.id "
              "JOIN Item ON Item.id = Owned_Item.item_id "
              "JOIN Publisher ON Publisher.id = Item.publisher "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Member ON requestee_id = Member.id "
              "JOIN "
                  "(SELECT Loan.id AS inner_loan_id, Member.id as owner_id, "
                  "username AS owner_username, email AS owner_email "
                  "FROM Member "
                  "JOIN Owned_Item ON Member.id = Owned_Item.member_id "
                  "JOIN Loan ON Owned_Item.id = Loan.owned_item_id) "
              "AS Owner ON owner_id = Owned_Item.member_id "
              "AND inner_loan_id = Loan.id "
              "WHERE requestee_id = " << userId << " "
              "ORDER BY start_data ASC, Loan_Request.id ASC "
              "LIMIT 15 OFFSET " << offset << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        numRequests = result->size();
        if (numRequests > 0) {
            requests = new (std::nothrow) LoanRequest[numRequests];
        }
        if (numRequests != 0) {
            index = 0;
            while (result->next()) {
                request = &requests[index];
                /// Set loan's data.
                request->setRequestId(result->value(0).toULongLong());
                request->setRequestStatus(result->value(1).toULongLong());
                request->setReplySent(result->value(2).toBool());
                request->setId(result->value(3).toULongLong());
                request->setStartDate(result->value(6).toDate());
                
                interval.seekp(interval.beg);
                interval << result->value(7).toString().toAscii().data();
                interval.seekg(interval.beg);
                interval >> days;
                request->setDuration(QDateTime(request->getStartDate().addDays(days)));
                request->setStatus(result->value(8).toULongLong());
                /// Set item's data.
                item = new OwnedItem();
                item->setId(result->value(9).toULongLong());
                item->setTitle(result->value(10).toString().toAscii().data());
                item->setGenre(result->value(11).toString().toAscii().data());
                item->setPublisher(result->value(12).toString().toAscii().data());
                item->setYear(result->value(13).toUInt());
                item->setOwnedItemId(result->value(5).toULongLong());
                item->setItemType(result->value(14).toULongLong());
                item->setItemPolicy(result->value(15).toULongLong());
                request->setRequestedItem(item);
                /// Set requestee's data.
                member = new Member();
                member->setId(result->value(4).toULongLong());
                member->setUsername(result->value(16).toString().toAscii().data());
                member->setEmail(result->value(17).toString().toAscii().data());
                request->setRequestingMember(member);
                /// Set owner's data.
                owner = new Member();
                owner->setId(result->value(18).toULongLong());
                owner->setUsername(result->value(19).toString().toAscii().data());
                owner->setEmail(result->value(20).toString().toAscii().data());
                item->setOwner(owner);
                index++;
            }
        }
        delete result;
    }
    
    return requests;
}

LoanRequest * LoanModel::getUserMessagesPage(unsigned long long userId,
                                             int pageNumber, int & numRequests)
{
    LoanRequest * requests = 0;
    LoanRequest * request = 0;
    OwnedItem * item = 0;
    Member * member = 0;
    Member * owner = 0;
    stringstream stream(stringstream::out);
    stringstream interval(stringstream::in | stringstream::out);
    QueryResult * result;
    unsigned index;
    unsigned offset = (pageNumber - 1) * 10;
    int days;
    
    stream << "SELECT Loan_Request.id, reply_status, request_status, "
              "loan_id, requestee_id, owned_item_id, start_data, "
              "duration, Loan.status, Item.id AS e_item_id, title, "
              "Genre.genre, Publisher.publisher, year, Item.type, "
              "Owned_Item.policy, username, email, owner_id, "
              "owner_username, owner_email FROM Loan_Request "
              "JOIN Loan ON loan_id = Loan.id "
              "JOIN Owned_Item ON owned_item_id = Owned_Item.id "
              "JOIN Item ON Item.id = Owned_Item.item_id "
              "JOIN Publisher ON Publisher.id = Item.publisher "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Member ON requestee_id = Member.id "
              "JOIN "
                  "(SELECT Loan.id AS inner_loan_id, Member.id as owner_id, "
                  "username AS owner_username, email AS owner_email "
                  "FROM Member "
                  "JOIN Owned_Item ON Member.id = Owned_Item.member_id "
                  "JOIN Loan ON Owned_Item.id = Loan.owned_item_id) "
              "AS Owner ON owner_id = Owned_Item.member_id "
              "AND inner_loan_id = Loan.id "
              "WHERE owner_id = " << userId << " "
              "AND request_status = FALSE "
              "ORDER BY start_data ASC, Loan_Request.id ASC "
              "LIMIT 10 OFFSET " << offset << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        numRequests = result->size();
        if (numRequests > 0) {
            requests = new (std::nothrow) LoanRequest[numRequests];
        }
        if (numRequests != 0) {
            index = 0;
            while (result->next()) {
                request = &requests[index];
                /// Set loan's data.
                request->setRequestId(result->value(0).toULongLong());
                request->setRequestStatus(result->value(1).toULongLong());
                request->setReplySent(result->value(2).toBool());
                request->setId(result->value(3).toULongLong());
                request->setStartDate(result->value(6).toDate());
                
                interval.seekp(interval.beg);
                interval << result->value(7).toString().toAscii().data();
                interval.seekg(interval.beg);
                interval >> days;
                request->setDuration(QDateTime(request->getStartDate().addDays(days)));
                request->setStatus(result->value(8).toULongLong());
                /// Set item's data.
                item = new OwnedItem();
                item->setId(result->value(9).toULongLong());
                item->setTitle(result->value(10).toString().toAscii().data());
                item->setGenre(result->value(11).toString().toAscii().data());
                item->setPublisher(result->value(12).toString().toAscii().data());
                item->setYear(result->value(13).toUInt());
                item->setOwnedItemId(result->value(5).toULongLong());
                item->setItemType(result->value(14).toULongLong());
                item->setItemPolicy(result->value(15).toULongLong());
                request->setRequestedItem(item);
                /// Set requestee's data.
                member = new Member();
                member->setId(result->value(4).toULongLong());
                member->setUsername(result->value(16).toString().toAscii().data());
                member->setEmail(result->value(17).toString().toAscii().data());
                request->setRequestingMember(member);
                /// Set owner's data.
                owner = new Member();
                owner->setId(result->value(18).toULongLong());
                owner->setUsername(result->value(19).toString().toAscii().data());
                owner->setEmail(result->value(20).toString().toAscii().data());
                item->setOwner(owner);
                index++;
            }
        }
        delete result;
    }
    
    return requests;
}

string * LoanModel::getRequestMessage(unsigned long long requestId)
{
    string * message = 0;
    stringstream stream(stringstream::out);
    QueryResult * result;
    
    stream << "SELECT id, message FROM Loan_Request "
              "WHERE id = " << requestId << ";";
    
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            message = new string();
            *message = result->value(1).toString().toAscii().data();
        }
        delete result;
    }
    
    return message; 
}

LoanRequest * LoanModel::getLoanRequest(unsigned long long requestId)
{
    LoanRequest * request = 0;
    OwnedItem * item = 0;
    Member * member = 0;
    Member * owner = 0;
    stringstream stream(stringstream::out);
    stringstream interval(stringstream::in | stringstream::out);
    QueryResult * result;
    int days;
    
    stream << "SELECT Loan_Request.id, reply_status, request_status, "
              "loan_id, requestee_id, owned_item_id, start_data, "
              "duration, Loan.status, Item.id AS e_item_id, title, "
              "Genre.genre, Publisher.publisher, year, Item.type, "
              "Owned_Item.policy, username, email, owner_id, "
              "owner_username, owner_email FROM Loan_Request "
              "JOIN Loan ON loan_id = Loan.id "
              "JOIN Owned_Item ON owned_item_id = Owned_Item.id "
              "JOIN Item ON Item.id = Owned_Item.item_id "
              "JOIN Publisher ON Publisher.id = Item.publisher "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Member ON requestee_id = Member.id "
              "JOIN "
                  "(SELECT Loan.id AS inner_loan_id, Member.id as owner_id, "
                  "username AS owner_username, email AS owner_email "
                  "FROM Member "
                  "JOIN Owned_Item ON Member.id = Owned_Item.member_id "
                  "JOIN Loan ON Owned_Item.id = Loan.owned_item_id) "
              "AS Owner ON owner_id = Owned_Item.member_id "
              "AND inner_loan_id = Loan.id "
              "WHERE Loan_Request.id = " << requestId << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            request = new LoanRequest();
            /// Set loan's data.
            request->setRequestId(result->value(0).toULongLong());
            request->setRequestStatus(result->value(1).toULongLong());
            request->setReplySent(result->value(2).toBool());
            request->setId(result->value(3).toULongLong());
            request->setStartDate(result->value(6).toDate());
            
            interval.seekp(interval.beg);
            interval << result->value(7).toString().toAscii().data();
            interval.seekg(interval.beg);
            interval >> days;
            request->setDuration(QDateTime(request->getStartDate().addDays(days)));
            request->setStatus(result->value(8).toULongLong());
            /// Set item's data.
            item = new OwnedItem();
            item->setId(result->value(9).toULongLong());
            item->setTitle(result->value(10).toString().toAscii().data());
            item->setGenre(result->value(11).toString().toAscii().data());
            item->setPublisher(result->value(12).toString().toAscii().data());
            item->setYear(result->value(13).toUInt());
            item->setOwnedItemId(result->value(5).toULongLong());
            item->setItemType(result->value(14).toULongLong());
            item->setItemPolicy(result->value(15).toULongLong());
            request->setRequestedItem(item);
            /// Set requestee's data.
            member = new Member();
            member->setId(result->value(4).toULongLong());
            member->setUsername(result->value(16).toString().toAscii().data());
            member->setEmail(result->value(17).toString().toAscii().data());
            request->setRequestingMember(member);
            /// Set owner's data.
            owner = new Member();
            owner->setId(result->value(18).toULongLong());
            owner->setUsername(result->value(19).toString().toAscii().data());
            owner->setEmail(result->value(20).toString().toAscii().data());
            item->setOwner(owner);
        }
        delete result;
    }
    
    return request;
}

bool LoanModel::rejectLoanRequest(unsigned long long requestId)
{
    stringstream stream(stringstream::out);
    bool requestUpdated = false;
    bool loanUpdated = false;
    
    stream << "UPDATE Loan_Request SET reply_status = 3, "
              "request_status = TRUE WHERE id = " << requestId << ";";
    
    requestUpdated = dbCon.nonQuery(stream.str());
    
    stream.seekp(stream.beg);
    stream << "UPDATE Loan SET status = 5 "
              "FROM Loan_Request "
              "WHERE Loan_Request.loan_id = Loan.id "
              "AND Loan_Request.id = " << requestId << ";";
              
    loanUpdated = dbCon.nonQuery(stream.str());
    
    return (requestUpdated && loanUpdated);
}

bool LoanModel::acceptLoanRequest(unsigned long long requestId)
{
    stringstream stream(stringstream::out);
    bool requestUpdated = false;
    bool loanUpdated = false;
    
    stream << "UPDATE Loan_Request SET reply_status = 2, "
              "request_status = TRUE WHERE id = " << requestId << ";";
    
    requestUpdated = dbCon.nonQuery(stream.str());
    
    stream.seekp(stream.beg);
    stream << "UPDATE Loan SET status = 1 "
              "FROM Loan_Request "
              "WHERE Loan_Request.loan_id = Loan.id "
              "AND Loan_Request.id = " << requestId << ";";
              
    loanUpdated = dbCon.nonQuery(stream.str());
    
    return (requestUpdated && loanUpdated);
}

