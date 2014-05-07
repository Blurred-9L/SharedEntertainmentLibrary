#include "SELController.h"
#include "../Model/LoginModel.h"
#include "../Model/Error.h"

SELController::SELController(QObject * parent) :
    QObject(parent), activeUserId(0), loginModel(0)
{
    loginModel = new (std::nothrow) LoginModel();
    if (loginModel == 0) {
        Error::raiseError(Error::ERROR_OUT_OF_MEMORY, true);
    }
}

SELController::~SELController()
{
    if (loginModel != 0) {
        delete loginModel;
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
