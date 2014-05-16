#include "MemberModel.h"
#include "Member.h"
#include "../DB/DBConnection.h"
#include "../DB/QueryResult.h"

#include <sstream>
using std::stringstream;

MemberModel::MemberModel() :
    dbCon(DBConnection::getInstance())
{
}

MemberModel::~MemberModel()
{
}

Member * MemberModel::getMemberData(unsigned long long id)
{
    Member * member = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT id, username, email, password FROM Member "
              "WHERE id = " << id << ";";
    
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            member = new Member();
            member->setId(id);
            member->setUsername(result->value(1).toString().toAscii().data());
            member->setEmail(result->value(2).toString().toAscii().data());
            member->setPassword(result->value(3).toString().toAscii().data());
        }
        delete result;
    }
    
    return member;
}
