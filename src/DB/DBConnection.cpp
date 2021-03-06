#include "DBConnection.h"
#include "QueryResult.h"
#include "../Model/Error.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>

///
const char * _DB_DRIVER_NAME = "QPSQL";
///
const unsigned _DB_DATA_SIZE = 4;
///
const unsigned _HOST_IDX = 0;
///
const unsigned _DB_NAME_IDX = 1;
///
const unsigned _DB_USER_IDX = 2;
///
const unsigned _DB_PSWD_IDX = 3;


DBConnection * DBConnection::dbCon = 0;

///
string * getConnectionData();

/**
 *  @details
 */
DBConnection::DBConnection()
{
    string * connectionData = 0;
    bool gotData = false;
    bool dbOpen = false;
    
    db = QSqlDatabase::addDatabase(_DB_DRIVER_NAME);
    connectionData = getConnectionData();
    gotData = connectionData != 0;
    if (gotData) {
        db.setHostName(connectionData[_HOST_IDX].c_str());
        db.setDatabaseName(connectionData[_DB_NAME_IDX].c_str());
        db.setUserName(connectionData[_DB_USER_IDX].c_str());
        db.setPassword(connectionData[_DB_PSWD_IDX].c_str());
        dbOpen = db.open();
        delete [] connectionData;
        if (!dbOpen) {
            Error::raiseError(Error::ERROR_NO_CONNECTION, true);
        }
    } else {
        Error::raiseError(Error::ERROR_NO_CONNECTION, true);
    }
}

/**
 *  @details
 */
DBConnection::~DBConnection()
{
    if (db.isOpen()) {
        db.close();
    }
}

/**
 *  @details
 */
QueryResult * DBConnection::query(const string & queryString) const
{
    QSqlQuery * queryObj = 0;
    bool ok;
    QueryResult * result = 0;
    
    queryObj = new (std::nothrow) QSqlQuery();
    if (queryObj != 0) {
        ok = queryObj->exec(queryString.c_str());
        if (ok) {
            result = new (std::nothrow) QueryResult(queryObj);
            if (result == 0) {
                Error::raiseError(Error::ERROR_OUT_OF_MEMORY);
            }
        } else {
            Error::raiseError(Error::ERROR_QUERY_FAIL);
        }
    }
    
    return result;
}

/**
 *  @details
 */
bool DBConnection::nonQuery(const string & queryString) const
{
    QSqlQuery queryObj;
    bool ok = queryObj.exec(queryString.c_str());
    
    return ok;
}

/**
 *  @details
 */
const char * DBConnection::lastError() const
{
    return db.lastError().text().toAscii().data();
}

/**
 *  @details
 */
DBConnection & DBConnection::getInstance()
{
    if (dbCon == 0) {
        dbCon = new (std::nothrow) DBConnection();
        if (dbCon == 0) {
            Error::raiseError(Error::ERROR_NO_CONNECTION, true);
        }
    }
    
    return *dbCon;
}

/**
 *  @details
 */
void DBConnection::deleteInstance()
{
    if (dbCon != 0) {
        delete dbCon;
        dbCon = 0;
    }
}

/**
 *  @details
 */
bool DBConnection::hasFeature(QSqlDriver::DriverFeature feature)
{
    if (dbCon == 0) {
        getInstance();
    }
    return dbCon->db.driver()->hasFeature(feature);
}

/**
 *  @details
 */
string * getConnectionData()
{
    string * connectionData = 0;
    
    connectionData = new (std::nothrow) string[_DB_DATA_SIZE];
    if (connectionData != 0) {
        connectionData[_HOST_IDX] = "localhost";
        connectionData[_DB_NAME_IDX] = "SEL";
        connectionData[_DB_USER_IDX] = "blurred";
        connectionData[_DB_PSWD_IDX] = "blurred";
    }
    
    return connectionData;
}

