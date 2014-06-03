#include "QueryResult.h"
#include "DBConnection.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>

/**
 *  @details
 */
QueryResult::QueryResult(QSqlQuery * queryObj) :
    queryResult(queryObj)
{
}

/**
 *  @details
 */
QueryResult::~QueryResult()
{
    if (queryResult != 0) {
        delete queryResult;
    }
}

/**
 *  @details
 */
int QueryResult::at() const
{
    return queryResult->at();
}

/**
 *  @details
 */
bool QueryResult::first() const
{
    return queryResult->first();
}

/**
 *  @details
 */
bool QueryResult::last()
{
    return queryResult->last();
}

/**
 *  @details
 */
bool QueryResult::next() const
{
    return queryResult->next();
}

/**
 *  @details
 */
bool QueryResult::previous() const
{
    return queryResult->previous();
}

/**
 *  @details
 */
bool QueryResult::seek(int index)
{
    return queryResult->seek(index);
}

/**
 *  @details
 */
int QueryResult::size() const
{
    int numRows;
    int currentRecord;
    
    if (DBConnection::hasFeature(QSqlDriver::QuerySize)) {
        numRows = queryResult->size();
    } else {
        currentRecord = queryResult->at();
        queryResult->last();
        numRows = queryResult->at() + 1;
        queryResult->seek(currentRecord);
    }
    
    return numRows;
}

/**
 *  @details
 */
QVariant QueryResult::value(int index) const
{
    return queryResult->value(index);
}

