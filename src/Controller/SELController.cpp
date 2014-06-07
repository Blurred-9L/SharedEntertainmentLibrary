#include "SELController.h"
#include "../Model/EntertainmentItem.h"
#include "../Model/LoginModel.h"
#include "../Model/ItemModel.h"
#include "../Model/MemberModel.h"
#include "../Model/LoanModel.h"
#include "../Model/Error.h"
#include "../Model/OwnedItem.h"
#include "../Model/Member.h"
#include "../Model/Loan.h"
#include "../Model/LoanRequest.h"

SELController::SELController(QObject * parent) :
    QObject(parent), activeUserId(0), loginModel(0), itemModel(0),
    memberModel(0)
{
    loginModel = new (std::nothrow) LoginModel();
    if (loginModel == 0) {
        Error::raiseError(Error::ERROR_OUT_OF_MEMORY, true);
    }
    itemModel = new (std::nothrow) ItemModel();
    if (itemModel == 0) {
        Error::raiseError(Error::ERROR_OUT_OF_MEMORY, true);
    }
    memberModel = new (std::nothrow) MemberModel();
    if (memberModel == 0) {
        Error::raiseError(Error::ERROR_OUT_OF_MEMORY, true);
    }
    loanModel = new (std::nothrow) LoanModel();
    if (loanModel == 0) {
        Error::raiseError(Error::ERROR_OUT_OF_MEMORY, true);
    }
    
    /// Updates loans status.
    loanModel->updateLoanStatuses();
}

SELController::~SELController()
{
    if (loginModel != 0) {
        delete loginModel;
    }
    if (itemModel != 0) {
        delete itemModel;
    }
    if (memberModel != 0) {
        delete memberModel;
    }
    if (loanModel != 0) {
        delete loanModel;
    }
}

bool SELController::memberLogIn(const string & username, const string & password)
{
    bool success = true;
    
    activeUserId = loginModel->tryLogin(username, password);
    
    if (activeUserId == 0) {
        success = false;
    }
    
    return success;
}

EntertainmentItem * SELController::retrieveLibraryPage(int pageToGet, int & numItems)
{
    EntertainmentItem * items = 0;
    
    items = itemModel->getItemsOnPage(pageToGet, numItems);
    
    return items;
}

EntertainmentItem * SELController::retrieveItem(unsigned long long id, unsigned long long & type)
{
    EntertainmentItem * item = 0;
    
    item = itemModel->getItem(id, type);
    
    return item;
}

OwnedItem * SELController::retrieveUserLibraryPage(int pageToGet, int & numItems)
{
    OwnedItem * items = 0;
    
    items = itemModel->getUserItemsOnPage(activeUserId, pageToGet, numItems);
    
    return items;
}

unsigned long long SELController::retrieveItemId(unsigned long long ownedItemId)
{
    unsigned long long id = 0;
    
    id = itemModel->getItemId(ownedItemId);
    
    return id;
}

unsigned long long SELController::retrieveItemPolicy(unsigned long long ownedItemId)
{
    unsigned long long policy;
    
    policy = itemModel->getItemPolicy(ownedItemId);
    
    return policy;
}

bool SELController::changeItemPolicy(unsigned long long ownedItemId, int policy)
{
    bool success = false;
    
    success = itemModel->updateItemPolicy(ownedItemId, policy);
    
    return success;
}

Member * SELController::retrieveData()
{
    Member * member = 0;
    
    member = memberModel->getMemberData(activeUserId);
    
    return member;
}

bool SELController::checkUserOwnsItem(unsigned long long itemId)
{
    bool itemOwned = false;
    
    itemOwned = itemModel->checkIfOwned(itemId, activeUserId);
    
    return itemOwned;
}

bool SELController::addItemToUserLibrary(unsigned long long itemId)
{
    bool success = false;
    
    success = itemModel->linkToMember(itemId, activeUserId);
    
    return success;
}

OwnedItem * SELController::retrieveOwners(unsigned long long itemId, int & numItems)
{
    OwnedItem * items = 0;
    
    items = itemModel->getOwners(itemId, activeUserId, numItems);
    
    return items;
}

bool SELController::scheduleAutomaticLoan(OwnedItem & item)
{
    bool success = false;
    bool lastLoanExists = false;
    Member * requestee = memberModel->getMemberData(activeUserId);
    OwnedItem * requestedItem = new OwnedItem(item);
    Loan * loan = 0;
    QDate startDate, endDate;
    
    /// Get last loan of item.
    loan = loanModel->getLastLoan(item.getOwnedItemId());
    if (loan != 0) {
        loan->setRequestingMember(requestee);
        loan->setRequestedItem(requestedItem);
        lastLoanExists = true;
    }
    
    if (!lastLoanExists) {
        /// Loan immediately.
        startDate = QDate::currentDate().addDays(1);
        success = loanModel->registerLoan(requestee->getId(), requestedItem->getOwnedItemId(), startDate,
                                          QDateTime(startDate).addDays(DEFAULT_LOAN_DURATION),
                                          LoanModel::STATUS_INACTIVE);
    } else {
        endDate = loan->getEndingDate();
        if (endDate <= QDate::currentDate()) {
            /// Loan immediately.
            if (endDate == QDate::currentDate()) {
                startDate = QDate::currentDate().addDays(2);
            } else {
                startDate = QDate::currentDate().addDays(1);
            }
            success = loanModel->registerLoan(requestee->getId(), requestedItem->getOwnedItemId(), startDate,
                                              QDateTime(startDate).addDays(DEFAULT_LOAN_DURATION),
                                              LoanModel::STATUS_INACTIVE);
        } else {
            /// Add a week to start date and schedule loan.
            startDate = endDate.addDays(7);
            success = loanModel->registerLoan(requestee->getId(), requestedItem->getOwnedItemId(), startDate,
                                              QDateTime(startDate).addDays(DEFAULT_LOAN_DURATION),
                                              LoanModel::STATUS_INACTIVE);
        }
        delete loan;
    }
    
    return success;
}

bool SELController::checkIfActiveLoan(unsigned long long ownedItemId)
{
    bool activeLoan = false;
    
    activeLoan = loanModel->loanExists(activeUserId, ownedItemId);
    
    return activeLoan;
}

bool SELController::processLoanRequest(OwnedItem & item, const string & message,
                                       const QDate & date, int daysOnLoan)
{
    bool loanOk = false;
    bool requestOk = false;
    Member * requestee = memberModel->getMemberData(activeUserId);
    OwnedItem * requestedItem = new OwnedItem(item);
    LoanRequest * request;
    QDateTime duration = QDateTime(date).addDays(daysOnLoan);
    unsigned long long loanId;
    
    request = new LoanRequest(requestee, requestedItem, date, duration, message.c_str());
    loanOk = loanModel->registerLoan(requestee->getId(), requestedItem->getOwnedItemId(), date,
                                     duration, LoanModel::STATUS_UNAVAILABLE);
    if (loanOk) {
        /// Obtain last loan id
        loanId = loanModel->getLastLoanId();
        request->setId(loanId);
        /// Register loan request.
        requestOk = loanModel->registerLoanRequest(*request, loanId);
    }
    
    delete request;
    
    return (loanOk && requestOk);
}

Loan * SELController::retrieveLoanPage(int pageToGet, int & numLoans)
{
    Loan * loans = 0;
    
    loans = loanModel->getUserLoansOnPage(activeUserId, pageToGet, numLoans);
    
    return loans;
}

LoanRequest * SELController::retrieveRequestPage(int pageToGet, int & numRequests)
{
    LoanRequest * requests = 0;
    
    requests = loanModel->getRequestsOfUserPage(activeUserId, pageToGet, numRequests);
    
    return requests;
}

