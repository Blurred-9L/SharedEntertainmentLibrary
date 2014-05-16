#ifndef MEMBER_MODEL_H
#define MEMBER_MODEL_H

class DBConnection;
class Member;

class MemberModel {
private:
    ///
    DBConnection & dbCon;
    
public:
    ///
    MemberModel();
    ///
    virtual ~MemberModel();
    ///
    Member * getMemberData(unsigned long long id);
    
};

#endif /// Not MEMBER_MODEL_H
