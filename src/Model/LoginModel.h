#ifndef LOGIN_MODEL_H
#define LOGIN_MODEL_H

#include <string>
using std::string;

class DBConnection;

class LoginModel {
private:
    DBConnection & dbCon;

public:
    ///
    LoginModel();
    ///
    virtual ~LoginModel();
    ///
    unsigned long long tryLogin(const string & username, const string & password) const;
};

#endif /// Not LOGIN_MODEL_H
