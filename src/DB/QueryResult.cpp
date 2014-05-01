#include "QueryResult.h"

#include <QtSql/QSqlQuery>

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
QVariant QueryResult::value(int index) const
{
    return queryResult->value(index);
}

