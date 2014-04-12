#ifndef OWNED_ITEM_H
#define OWNED_ITEM_H

#include "EntertainmentItem.h"

class Member;

/**
 *  @class  OwnedItem
 */
class OwnedItem : public EntertainmentItem {
private:
    ///
    unsigned itemType;
    ///
    unsigned itemPolicy;
    ///
    Member * owner;
    
public:
    /**
     *  @enum   ItemType
     */
    enum ItemType {
        TYPE_INVALID = 0
    };
    
    /**
     *  @enum   ItemPolicy
     */
    enum ItemPolicy {
        POLICY_FREE = 1
    };
    
    ///
    OwnedItem();
    ///
    OwnedItem(const string & title, const string & genre,
              const string & publisher, unsigned year, unsigned itemType,
              unsigned itemPolicy, Member * owner);
    ///
    virtual ~OwnedItem();
    ///
    unsigned getItemType() const;
    ///
    unsigned getItemPolicy() const;
    ///
    const Member & getOwner() const;
    ///
    Member & getOwner();
    ///
    void setItemType(unsigned itemType);
    ///
    void setItemPolicy(unsigned itemPolicy);
    ///
    void setOwner(Member * owner);
    ///
    bool hasFreePolicy() const;
};

#endif /// Not OWNED_ITEM_H
