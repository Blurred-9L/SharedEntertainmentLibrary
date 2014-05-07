#ifndef ITEM_MODEL_H
#define ITEM_MODEL_H

class DBConnection;

class ItemModel {
private:
    ///
    DBConnection & dbCon;

public:
    ///
    ItemModel();
    ///
    virtual ~ItemModel();
    
};

#endif /// Not ITEM_MODEL_H
