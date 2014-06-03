#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>

#include <string>
using std::string;

class QueryResult;

/**
 *  @class  DBConnection
 */
class DBConnection {
private:
    ///
    static DBConnection * dbCon;
    ///
    QSqlDatabase db;

    ///
    DBConnection();
    
public:
    ///
    virtual ~DBConnection();
    ///
    virtual QueryResult * query(const string & queryString) const;
    ///
    virtual bool nonQuery(const string & queryString) const;
    ///
    virtual const char * lastError() const;
    
    
    ///
    static DBConnection & getInstance();
    ///
    static void deleteInstance();
    ///
    static bool hasFeature(QSqlDriver::DriverFeature feature);
};

#endif /// Not DB_CONNECTION_H
