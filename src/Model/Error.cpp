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
