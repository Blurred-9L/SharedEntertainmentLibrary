#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include <QtCore/QVariant>

class QSqlQuery;

/**
 *  @class  QueryResult
 */
class QueryResult {
private:
    ///
    QSqlQuery * queryResult;
    
public:
    ///
    explicit QueryResult(QSqlQuery * queryObj);
    ///
    virtual ~QueryResult();
    ///
    int at() const;
    ///
    bool first() const;
    ///
    bool last();
    ///
    bool next() const;
    ///
    bool previous() const;
    ///
    bool seek(int index);
    ///
    int size() const;
    ///
    QVariant value(int index) const;
};

#endif /// Not QUERY_RESULT_H
