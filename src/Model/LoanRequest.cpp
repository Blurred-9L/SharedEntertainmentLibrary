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

bool LoanRequest::getReplySent() const
{
    return replySent;
}

unsigned LoanRequest::getRequestStatus() const
{
    return requestStatus;
}

const string & LoanRequest::getMessage() const
{
    return message;
}

void LoanRequest::setReplySent(bool replySent)
{
    this->replySent = replySent;
}

void LoanRequest::setRequestStatus(unsigned requestStatus)
{
    this->requestStatus = requestStatus;
}

void LoanRequest::setMessage(const string & message)
{
    this->message = message;
}
