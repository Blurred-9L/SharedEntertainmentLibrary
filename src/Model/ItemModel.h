#ifndef ITEM_MODEL_H
#define ITEM_MODEL_H

class DBConnection;
class EntertainmentItem;
class Book;
class MusicAlbum;
class Videogame;

class ItemModel {
private:
    ///
    DBConnection & dbCon;

public:
    ///
    ItemModel();
    ///
    virtual ~ItemModel();
    ///
    virtual EntertainmentItem * getItemsOnPage(int pageNumber, int & numItems);
    ///
    virtual EntertainmentItem * getItem(unsigned long long id, unsigned long long & itemType);
    ///
    virtual unsigned long long getItemType(unsigned long long id);
    ///
    virtual Book * getBookItem(unsigned long long id);
    ///
    virtual bool getBookAuthors(Book * book);
    ///
    virtual MusicAlbum * getMusicItem(unsigned long long id);
    ///
    virtual Videogame * getVideogameItem(unsigned long long id);
};

#endif /// Not ITEM_MODEL_H
