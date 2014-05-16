#include "Error.h"

#include <cstdlib>

#include <QtGui/QMessageBox>
#include <QtCore/QString>

Error::Error(unsigned errorNo) :
    errorNo(errorNo)
{
    errorString = Error::getErrorString(errorNo);
}

Error::~Error()
{
}

unsigned Error::getErrorNo() const
{
    return errorNo;
}

const string & Error::getErrorString() const
{
    return errorString;
}

string Error::getErrorString(unsigned errorNo)
{
    string errorString = "";
    
    switch (errorNo) {
    case ERROR_NO_CONNECTION:
        errorString = "Error Code 1: Database connection could not be established.";
        break;
    case ERROR_OUT_OF_MEMORY:
        errorString = "Error Code 2: Program is out of memory.";
        break;
    case ERROR_NO_SUCH_PAGE_MLIB:
        errorString = "Error Code 3: Could not request new main library page.";
        break;
    case ERROR_UNKNOWN_ITEM_TYPE:
        errorString = "Error Code 4: Could not determine item type.";
        break;
    case ERROR_ITEM_ID_NOT_FOUND:
        errorString = "Error Code 5: Could not find requested item id.";
        break;
    case ERROR_ITEM_SELECTION_ERROR:
        errorString = "Error Code 6: More than one item selected.";
        break;
    case ERROR_NO_ITEM_SELECTED:
        errorString = "Error Code 7: No item selected.";
        break;
    case ERROR_NO_SUCH_PAGE_ULIB:
        errorString = "Error Code 8: Could not request new user library page.";
        break;
    case ERROR_NO_SUCH_PAGE_LOAN:
        errorString = "Error Code 9: Could not request new user loans page.";
        break;
    case ERROR_NO_SUCH_PAGE_REQ:
        errorString = "Error Code 10: Could not request new user loan requests page.";
        break;
    case ERROR_REQ_ID_NOT_FOUND:
        errorString = "Error Code 11: Could not find requested loan request id.";
        break;
    case ERROR_USERNAME_LONG:
        errorString = "Error Code 12: Username was too long.";
        break;
    case ERROR_USERNAME_FORMAT:
        errorString = "Error Code 13: Invalid character found on username.";
        break;
    case ERROR_PASSWORD_LONG:
        errorString = "Error Code 14: Password was too long.";
        break;
    case ERROR_PASSWORD_FORMAT:
        errorString = "Error Code 15: Invalid character found on password.";
        break;
    case ERROR_USERNAME_SHORT:
        errorString = "Error Code 16: Username was too short.";
        break;
    case ERROR_PASSWORD_SHORT:
        errorString = "Error Code 17: Password was too short.";
        break;
    case ERROR_LOGIN_FAIL:
        errorString = "Error Code 18: Could not login with the given username and password.";
        break;
    case ERROR_QUERY_FAIL:
        errorString = "Error Code 19: The query could not be completed.";
        break;
    case ERROR_ITEM_ID_FAIL:
        errorString = "Error Code 20: The item's id was not found inside the database.";
        break;
    case ERROR_POLICY_CHANGE_FAIL:
        errorString = "Error Code 21: The item's loan policy could not be changed.";
        break;
    case ERROR_ITEM_OWNED:
        errorString = "Error Code 22: The item is already on your library.";
        break;
    case ERROR_ITEM_ADD_FAIL:
        errorString = "Error Code 23: The item could not be added to your library...";
        break;
    case ERROR_PAGE_RELOAD_FAIL:
        errorString = "Error Code 24: An item page could not be realoaded. Data displayed might not match "
                      "current data.";
        break;
    default:
        break;
    }
    
    return errorString;
}

void Error::raiseError(unsigned errorNo, bool abortProgram)
{
    QString errorString = Error::getErrorString(errorNo).c_str();
    
    QMessageBox::critical(0, "Error!", errorString);
    if (abortProgram) {
        exit(1);
    }
}
