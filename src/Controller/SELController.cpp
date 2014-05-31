#include "SELController.h"
#include "../Model/EntertainmentItem.h"
#include "../Model/LoginModel.h"
#include "../Model/ItemModel.h"
#include "../Model/MemberModel.h"
#include "../Model/Error.h"
#include "../Model/OwnedItem.h"

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
}

SELController::~SELController()
{
    if (loginModel != 0) {
        delete loginModel;
    }
    if (itemModel != 0) {
        delete itemModel;
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
    
    /// Get last loan of item. 
    /// If no last loan or loan is over, loan immediately.
    /// If last loan is not over, get ending date.
    /// Add a week to ending date.
    /// Loan item   
    
    return success;
}

