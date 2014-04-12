#include "OwnedItem.h"
#include "Member.h"

OwnedItem::OwnedItem() :
    EntertainmentItem(), itemType(0), itemPolicy(0), owner(0)
{
    owner = new Member();
}

OwnedItem::OwnedItem(const string & title, const string & genre,
                     const string & publisher, unsigned year, int itemType,
                     int itemPolicy, Member * owner) :
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

int OwnedItem::getItemType() const
{
    return itemType;
}

int OwnedItem::getItemPolicy() const
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

void OwnedItem::setItemType(int itemType)
{
    this->itemType = itemType;
}

void OwnedItem::setItemPolicy(int itemPolicy)
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
