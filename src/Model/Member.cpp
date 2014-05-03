#include "Member.h"

Member::Member() :
    id(0), username(), email(), password()
{
}

Member::Member(const string & username) :
    id(0), username(username), email(), password()
{
}

Member::~Member()
{
}

unsigned long long Member::getId() const
{
    return id;
}

const string & Member::getUsername() const
{
    return username;
}

const string & Member::getEmail() const
{
    return email;
}

const string & Member::getPassword() const
{
    return password;
}

void Member::setId(unsigned long long id)
{
    this->id = id;
}

void Member::setUsername(const string & username)
{
    this->username = username;
}

void Member::setEmail(const string & email)
{
    this->email = email;
}

void Member::setPassword(const string & password)
{
    this->password = password;
}
