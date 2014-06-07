#include "LoanRequest.h"
#include "Member.h"
#include "OwnedItem.h"

LoanRequest::LoanRequest() :
    Loan(), replySent(false), requestStatus(0), message()
{
}

LoanRequest::LoanRequest(Member * requestingMember, OwnedItem * requestedItem,
                         const QDate & startDate, const QDateTime & duration,
                         const string & message) :
    Loan(requestingMember, requestedItem, startDate, duration),
    replySent(false), requestStatus(0), message(message)
{
}

LoanRequest::~LoanRequest()
{
}

unsigned long long LoanRequest::getRequestId() const
{
    return requestId;
}

bool LoanRequest::getReplySent() const
{
    return replySent;
}

unsigned long long LoanRequest::getRequestStatus() const
{
    return requestStatus;
}

const string & LoanRequest::getMessage() const
{
    return message;
}

void LoanRequest::setRequestId(unsigned long long requestId)
{
    this->requestId = requestId;
}

void LoanRequest::setReplySent(bool replySent)
{
    this->replySent = replySent;
}

void LoanRequest::setRequestStatus(unsigned long long requestStatus)
{
    this->requestStatus = requestStatus;
}

void LoanRequest::setMessage(const string & message)
{
    this->message = message;
}

string LoanRequest::toString() const
{
    string returnString = Loan::toString();
    
    returnString = getRequestedItem().getTitle();
    returnString += " - ";
    returnString += getRequestedItem().getOwner().getUsername();
    returnString += " - ";
    returnString += getRequestStatusString(requestStatus);
    
    return returnString;
}

string LoanRequest::getRequestStatusString(unsigned long long requestStatus)
{
    string requestStatusString = "";
    
    switch (requestStatus) {
    case REQUEST_STATUS_UNANSWERED:
        requestStatusString = "Unanswered";
        break;
    case REQUEST_STATUS_ACCEPTED:
        requestStatusString = "Accepted";
        break;
    case REQUEST_STATUS_REJECTED:
        requestStatusString = "Rejected";
        break;
    default:
        break;
    }
    
    return requestStatusString;
}
