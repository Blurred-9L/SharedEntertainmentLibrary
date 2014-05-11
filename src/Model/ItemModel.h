#ifndef ITEM_MODEL_H
#define ITEM_MODEL_H

class DBConnection;
class EntertainmentItem;
class OwnedItem;
class Book;
class Movie;
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
    virtual OwnedItem * getUserItemsOnPage(unsigned long long userId, int pageNumber, int & numItems);
    ///
    virtual EntertainmentItem * getItem(unsigned long long id, unsigned long long & itemType);
    ///
    virtual unsigned long long getItemType(unsigned long long id);
    ///
    virtual Book * getBookItem(unsigned long long id);
    ///
    virtual bool getBookAuthors(Book * book);
    ///
    virtual Movie * getMovieItem(unsigned long long id);
    ///
    virtual bool getMovieActors(Movie * movie);
    ///
    virtual MusicAlbum * getMusicItem(unsigned long long id);
    ///
    virtual Videogame * getVideogameItem(unsigned long long id);
    ///
    virtual unsigned long long getItemId(unsigned long long ownedItemId);
    ///
    virtual unsigned long long getItemPolicy(unsigned long long ownedItemId);
    ///
    virtual bool updateItemPolicy(unsigned long long ownedItemId, int policy);
};

#endif /// Not ITEM_MODEL_H
