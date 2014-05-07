#include "ItemModel.h"
#include "../DB/DBConnection.h"
#include "../DB/QueryResult.h"

ItemModel::ItemModel() :
    dbCon(DBConnection::getInstance())
{
}

ItemModel::~ItemModel()
{
}
