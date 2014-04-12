#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using std::string;

/**
 *  @class
 */
class Member {
private:
    ///
    unsigned id;
    ///
    string username;
    ///
    string email;
    ///
    string password;
    
public:
    ///
    Member();
    ///
    explicit Member(const string & username);
    ///
    virtual ~Member();
    ///
    unsigned getId() const;
    ///
    const string & getUsername() const;
    ///
    const string & getEmail() const;
    ///
    const string & getPassword() const;
    ///
    void setId(unsigned id);
    ///
    void setUsername(const string & username);
    ///
    void setEmail(const string & email);
    ///
    void setPassword(const string & password);
};

#endif /// Not MEMBER_H
