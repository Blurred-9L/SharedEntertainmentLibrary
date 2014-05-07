#include "LoginModel.h"
#include "../DB/DBConnection.h"
#include "../DB/QueryResult.h"

#include <sstream>
using std::stringstream;

#include <QtCore/QString>

LoginModel::LoginModel() :
    dbCon(DBConnection::getInstance())
{
}

LoginModel::~LoginModel()
{
}

long long LoginModel::tryLogin(const string & username, const string & password) const
{
    stringstream stream(stringstream::out);
    string dbUsername, dbPassword;
    QueryResult * result;
    long long userId = 0;
    
    stream << "SELECT id, username, password FROM Member "
              "WHERE username=\'" << username << "\' AND "
              "password=\'" << password << "\';";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            dbUsername = result->value(1).toString().toAscii().data();
            dbPassword = result->value(2).toString().toAscii().data();
            if ((dbUsername == username) && (dbPassword == password)) {
                userId = result->value(0).toLongLong();
            }
        }
        delete result;
    }
    
    return userId;
}
