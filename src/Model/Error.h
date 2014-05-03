#ifndef ERROR_H
#define ERROR_H

#include <string>
using std::string;

/**
 *  @class  Error
 */
class Error {
private:
    ///
    unsigned errorNo;
    ///
    string errorString;

public:
    /**
     *  @enum   ErrorType
     */
    enum ErrorType {
        INVALID_ERROR,
        ERROR_NO_CONNECTION,
        ERROR_OUT_OF_MEMORY,
        ERROR_NO_SUCH_PAGE_MLIB,
        ERROR_UNKNOWN_ITEM_TYPE,
        ERROR_ITEM_ID_NOT_FOUND,
        ERROR_ITEM_SELECTION_ERROR,
        ERROR_NO_ITEM_SELECTED,
        ERROR_NO_SUCH_PAGE_ULIB,
        ERROR_NO_SUCH_PAGE_LOAN,
        ERROR_NO_SUCH_PAGE_REQ,
        ERROR_REQ_ID_NOT_FOUND
    };
    
    ///
    explicit Error(unsigned errorNo);
    ///
    virtual ~Error();
    ///
    unsigned getErrorNo() const;
    ///
    const string & getErrorString() const;
    
    ///
    static string getErrorString(unsigned errorNo);
    ///
    static void raiseError(unsigned errorNo, bool abortProgram = false);
    
};

#endif /// Not ERROR_H
