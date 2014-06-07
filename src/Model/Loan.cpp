#include "Loan.h"
#include "Member.h"
#include "OwnedItem.h"

Loan::Loan() :
    requestingMember(0), requestedItem(0), startDate(), duration(),
    status(0)
{
    requestingMember = new Member();
    requestedItem = new OwnedItem();
}

Loan::Loan(Member * requestingMember, OwnedItem * requestedItem,
           const QDate & startDate, const QDateTime & duration) :
    requestingMember(requestingMember), requestedItem(requestedItem),
    startDate(startDate.year(), startDate.month(), startDate.day()),
    duration(duration), status(0)
{
}

Loan::~Loan()
{
    if (requestingMember != 0) {
        delete requestingMember;
    }
    if (requestedItem != 0) {
        delete requestedItem;
    }
}

unsigned long long Loan::getId() const
{
    return id;
}

const Member & Loan::getRequestingMember() const
{
    return *requestingMember;
}

Member & Loan::getRequestingMember()
{
    return *requestingMember;
}

const OwnedItem & Loan::getRequestedItem() const
{
    return *requestedItem;
}

OwnedItem & Loan::getRequestedItem()
{
    return *requestedItem;
}

const QDate & Loan::getStartDate() const
{
    return startDate;
}

QDate & Loan::getStartDate()
{
    return startDate;
}

const QDateTime & Loan::getDuration() const
{
    return duration;
}

QDateTime & Loan::getDuration()
{
    return duration;
}

unsigned long long Loan::getStatus() const
{
    return status;
}

void Loan::setId(unsigned long long id)
{
    this->id = id;
}

void Loan::setRequestingMember(Member * requestingMember)
{
    if (this->requestingMember != 0) {
        delete this->requestingMember;
    }
    this->requestingMember = requestingMember;
}

void Loan::setRequestedItem(OwnedItem * requestedItem)
{
    if (this->requestedItem != 0) {
        delete this->requestedItem;
    }
    this->requestedItem = requestedItem;
}

void Loan::setStartDate(const QDate & startDate)
{
    this->startDate.setDate(startDate.year(), startDate.month(),
                            startDate.day());
}

void Loan::setDuration(const QDateTime & duration)
{
    this->duration.setDate(duration.date());
    this->duration.setTime(duration.time());
}

void Loan::setStatus(unsigned long long status)
{
    this->status = status;
}

string Loan::toString() const
{
    string returnString;
    
    returnString += requestedItem->getTitle();
    returnString += " - ";
    returnString += requestedItem->getOwner().getUsername();
    returnString += " - ";
    returnString += getStatusString(status);
    
    return returnString;
}

QDate Loan::getEndingDate() const
{
    return startDate.addDays(startDate.daysTo(duration.date()));
}

string Loan::getStatusString(unsigned long long status)
{
    string statusString = "";
    
    switch (status) {
    case LOAN_STATUS_INACTIVE:
        statusString = "Inactive";
        break;
    case LOAN_STATUS_ACTIVE:
        statusString = "Active";
        break;
    case LOAN_STATUS_ENDED:
        statusString = "Ended";
        break;
    case LOAN_STATUS_NOT_AVAILABLE:
        statusString = "Unavailable";
        break;
    case LOAN_STATUS_IMPOSSIBLE:
        statusString = "Impossible";
        break;
    default:
        break;
    }
    
    return statusString;
}
