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
