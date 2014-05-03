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
    unsigned long long ownedItemId;
    ///
    unsigned long long itemType;
    ///
    unsigned long long itemPolicy;
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
              const string & publisher, unsigned year,
              unsigned long long itemType,
              unsigned long long itemPolicy, Member * owner);
    ///
    virtual ~OwnedItem();
    ///
    unsigned long long getOwnedItemId() const;
    ///
    unsigned long long getItemType() const;
    ///
    unsigned long long getItemPolicy() const;
    ///
    const Member & getOwner() const;
    ///
    Member & getOwner();
    ///
    void setOwnedItemId(unsigned long long ownedItemId);
    ///
    void setItemType(unsigned long long itemType);
    ///
    void setItemPolicy(unsigned long long itemPolicy);
    ///
    void setOwner(Member * owner);
    ///
    bool hasFreePolicy() const;
};

#endif /// Not OWNED_ITEM_H
