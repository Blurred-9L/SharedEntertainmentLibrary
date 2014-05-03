#include "OwnedItem.h"
#include "Member.h"

OwnedItem::OwnedItem() :
    EntertainmentItem(), itemType(0), itemPolicy(0), owner(0)
{
    owner = new Member();
}

OwnedItem::OwnedItem(const string & title, const string & genre,
                     const string & publisher, unsigned year,
                     unsigned long long itemType,
                     unsigned long long itemPolicy, Member * owner) :
    EntertainmentItem(title, genre, publisher, year), itemType(itemType),
    itemPolicy(itemPolicy), owner(owner)
{
}

OwnedItem::~OwnedItem()
{
    if (owner != 0) {
        delete owner;
    }
}

unsigned long long OwnedItem::getOwnedItemId() const
{
    return ownedItemId;
}

unsigned long long OwnedItem::getItemType() const
{
    return itemType;
}

unsigned long long OwnedItem::getItemPolicy() const
{
    return itemPolicy;
}

const Member & OwnedItem::getOwner() const
{
    return *owner;
}

Member & OwnedItem::getOwner()
{
    return *owner;
}

void OwnedItem::setOwnedItemId(unsigned long long ownedItemId)
{
    this->ownedItemId = ownedItemId;
}

void OwnedItem::setItemType(unsigned long long itemType)
{
    this->itemType = itemType;
}

void OwnedItem::setItemPolicy(unsigned long long itemPolicy)
{
    this->itemPolicy = itemPolicy;
}

void OwnedItem::setOwner(Member * owner)
{
    if (this->owner != 0) {
        delete this->owner;
    }
    this->owner = owner;
}

bool OwnedItem::hasFreePolicy() const
{
    return itemPolicy == POLICY_FREE;
}
