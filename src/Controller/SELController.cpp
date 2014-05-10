#include "SELController.h"
#include "../Model/EntertainmentItem.h"
#include "../Model/LoginModel.h"
#include "../Model/ItemModel.h"
#include "../Model/Error.h"

SELController::SELController(QObject * parent) :
    QObject(parent), activeUserId(0), loginModel(0), itemModel(0)
{
    loginModel = new (std::nothrow) LoginModel();
    if (loginModel == 0) {
        Error::raiseError(Error::ERROR_OUT_OF_MEMORY, true);
    }
    itemModel = new (std::nothrow) ItemModel();
    if (itemModel == 0) {
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

