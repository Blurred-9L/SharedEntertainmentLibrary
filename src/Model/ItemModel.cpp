#include "ItemModel.h"
#include "EntertainmentItem.h"
#include "OwnedItem.h"
#include "Book.h"
#include "Movie.h"
#include "MusicAlbum.h"
#include "Videogame.h"
#include "Error.h"
#include "Member.h"
#include "../DB/DBConnection.h"
#include "../DB/QueryResult.h"

#include <sstream>
using std::stringstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

ItemModel::ItemModel() :
    dbCon(DBConnection::getInstance())
{
}

ItemModel::~ItemModel()
{
}

EntertainmentItem * ItemModel::getItemsOnPage(int pageNumber, int & numItems)
{
    EntertainmentItem * items = 0;
    EntertainmentItem * item;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    /// @todo Obtain contant from class instead of hardcoding it.
    int offset = (pageNumber - 1) * 20;
    int index;
    
    stream << "SELECT Item.id, title, Genre.genre, Publisher.publisher, "
              "year FROM Item "
              "JOIN Genre on Item.genre = Genre.id "
              "JOIN Publisher on Item.publisher = Publisher.id "
              "ORDER BY id ASC "
              "LIMIT 20 OFFSET " << offset << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        numItems = result->size();
        if (numItems > 0) {
            items = new (std::nothrow) EntertainmentItem[numItems];
        }
        if (items != 0) {
            index = 0;
            while (result->next()) {
                item = &items[index];
                item->setId(result->value(0).toULongLong());
                item->setTitle(result->value(1).toString().toAscii().data());
                item->setGenre(result->value(2).toString().toAscii().data());
                item->setPublisher(result->value(3).toString().toAscii().data());
                item->setYear(result->value(4).toUInt());
                index++;
            }
        }
        delete result;
    }
    
    return items;
}

OwnedItem * ItemModel::getUserItemsOnPage(unsigned long long userId,
                                          int pageNumber, int & numItems)
{
    OwnedItem * items = 0;
    OwnedItem * item = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    int offset = (pageNumber - 1) * 20;
    int index;
    
    stream << "SELECT Item.id as item_id, Owned_Item.id as owned_id, "
              "title, Genre.genre, Publisher.publisher, year, type FROM Item "
              "JOIN Genre on Item.genre = Genre.id "
              "JOIN Publisher on Item.publisher = Publisher.id "
              "JOIN Owned_Item on Item.id = Owned_Item.item_id "
              "WHERE Owned_Item.member_id = " << userId << " "
              "ORDER BY Item.id ASC "
              "LIMIT 20 OFFSET " << offset << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        numItems = result->size();
        if (numItems > 0) {
            items = new (std::nothrow) OwnedItem[numItems];
        }
        if (items != 0) {
            index = 0;
            while (result->next()) {
                item = &items[index];
                item->setId(result->value(0).toULongLong());
                item->setOwnedItemId(result->value(1).toULongLong());
                item->setTitle(result->value(2).toString().toAscii().data());
                item->setGenre(result->value(3).toString().toAscii().data());
                item->setPublisher(result->value(4).toString().toAscii().data());
                item->setYear(result->value(5).toUInt());
                item->setItemType(result->value(6).toULongLong());
                index++;
            }
        }
        delete result;
    }
    
    return items;
}

EntertainmentItem * ItemModel::getItem(unsigned long long id, unsigned long long & itemType)
{
    EntertainmentItem * item = 0;
    
    itemType = getItemType(id);
    switch (itemType) {
    case OwnedItem::TYPE_BOOK:
        item = getBookItem(id);
        break;
    case OwnedItem::TYPE_MOVIE:
        item = getMovieItem(id);
        break;
    case OwnedItem::TYPE_MUSIC:
        item = getMusicItem(id);
        break;
    case OwnedItem::TYPE_VIDEOGAME:
        item = getVideogameItem(id);
        break;
    default:
        Error::raiseError(Error::ERROR_ITEM_ID_FAIL);
        break;
    }
    
    return item;
}

unsigned long long ItemModel::getItemType(unsigned long long id)
{
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    unsigned long long itemType = 0;
    
    stream << "SELECT type from Item WHERE id = " << id << ";";
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            itemType = result->value(0).toULongLong();
        }
        delete result;
    }
    
    return itemType;
}

Book * ItemModel::getBookItem(unsigned long long id)
{
    Book * item = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT Item.id, title, Genre.genre, Publisher.publisher, "
              "year, isbn, num_pages FROM Item "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Publisher ON Item.publisher = Publisher.id "
              "JOIN Book_Data ON Item.book_id = Book_Data.id "
              "WHERE Item.id = " << id << ";";

    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            item = new Book();
            item->setId(result->value(0).toULongLong());
            item->setTitle(result->value(1).toString().toAscii().data());
            item->setGenre(result->value(2).toString().toAscii().data());
            item->setPublisher(result->value(3).toString().toAscii().data());
            item->setYear(result->value(4).toUInt());
            item->setIsbn(result->value(5).toString().toAscii().data());
            item->setNPages(result->value(6).toUInt());
            getBookAuthors(item);
        }
        delete result;
    }
    
    return item;
}

bool ItemModel::getBookAuthors(Book * book)
{
    vector<string> authors;
    string author;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    bool success = false;
    
    if (book != 0) {
        stream << "SELECT name || \' \' || last_name AS author FROM Item "
                  "JOIN Book_Data ON Item.book_id = Book_Data.id "
                  "JOIN Book_Author ON Book_Author.book_id = Book_Data.id "
                  "JOIN Person ON Book_Author.author_id = Person.id "
                  "WHERE Item.id = " << book->getId() << ";";
                  
        result = dbCon.query(stream.str());
        if (result != 0) {
            while (result->next()) {
                author = result->value(0).toString().toAscii().data();
                authors.push_back(author);
            }
            book->setAuthors(authors);
            delete result;
            success = true;
        }
    }
    
    return success;
}

Movie * ItemModel::getMovieItem(unsigned long long id)
{
    Movie * item = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT Item.id, title, Genre.genre, Publisher.publisher, "
              "year, name, duration, Rating.rating FROM Item "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Publisher ON Item.publisher = Publisher.id "
              "JOIN Movie_Data ON Item.movie_id = Movie_Data.id "
              "JOIN Person ON Movie_Data.director_id = Person.id "
              "JOIN Rating ON Movie_Data.rating = Rating.id "
              "WHERE Item.id = " << id << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            item = new Movie();
            item->setId(result->value(0).toULongLong());
            item->setTitle(result->value(1).toString().toAscii().data());
            item->setGenre(result->value(2).toString().toAscii().data());
            item->setPublisher(result->value(3).toString().toAscii().data());
            item->setYear(result->value(4).toUInt());
            item->setDirector(result->value(5).toString().toAscii().data());
            item->setDuration(result->value(6).toTime());
            item->setRating(result->value(7).toULongLong());
            getMovieActors(item);
        }
        delete result;
    }
    
    return item;
}

bool ItemModel::getMovieActors(Movie * movie)
{
    vector<string> actors;
    string actor;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    bool success = false;
    
    if (movie != 0) {
        stream << "SELECT name || ' ' || last_name AS actor FROM Item "
                  "JOIN Movie_Data ON Item.movie_id = Movie_Data.id "
                  "JOIN Movie_Actor ON Movie_Data.id = Movie_Actor.movie_id "
                  "JOIN Person ON Movie_Actor.actor_id = Person.id "
                  "WHERE Item.id = " << movie->getId() << " "
                  "ORDER BY actor ASC;";
                  
        result = dbCon.query(stream.str());
        if (result != 0) {
            while (result->next()) {
                actor = result->value(0).toString().toAscii().data();
                actors.push_back(actor);
            }
            movie->setMainActors(actors);
            delete result;
            success = true;
        }
    }
    
    return success;
}

MusicAlbum * ItemModel::getMusicItem(unsigned long long id)
{
    MusicAlbum * item = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT Item.id, title, Genre.genre, Publisher.publisher, "
              "year, name AS artist, num_tracks, duration FROM Item "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Publisher ON Item.publisher = Publisher.id "
              "JOIN Music_Data ON Item.music_id = Music_Data.id "
              "JOIN Artist ON Music_Data.artist_id = Artist.id "
              "WHERE Item.id = " << id << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            item = new MusicAlbum();
            item->setId(result->value(0).toULongLong());
            item->setTitle(result->value(1).toString().toAscii().data());
            item->setGenre(result->value(2).toString().toAscii().data());
            item->setPublisher(result->value(3).toString().toAscii().data());
            item->setYear(result->value(4).toUInt());
            item->setArtist(result->value(5).toString().toAscii().data());
            item->setNTracks(result->value(6).toUInt());
            item->setDuration(result->value(7).toTime());
        }
        delete result;
    }
    
    return item;
}

Videogame * ItemModel::getVideogameItem(unsigned long long id)
{
    Videogame * item = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT Item.id, title, Genre.genre, Publisher.publisher, "
              "year, esrb_rating, Videogame_Data.platform_id FROM Item "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Publisher ON Item.publisher = Publisher.id "
              "JOIN Videogame_Data ON Item.videogame_id = Videogame_Data.id "
              "WHERE Item.id = " << id << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            item = new Videogame();
            item->setId(result->value(0).toULongLong());
            item->setTitle(result->value(1).toString().toAscii().data());
            item->setGenre(result->value(2).toString().toAscii().data());
            item->setPublisher(result->value(3).toString().toAscii().data());
            item->setYear(result->value(4).toUInt());
            item->setEsrbRating(result->value(5).toULongLong());
            item->setPlatform(result->value(6).toULongLong());
        }
        delete result;
    }
    
    return item;
}

unsigned long long ItemModel::getItemId(unsigned long long ownedItemId)
{
    unsigned long long id = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT Item.id FROM Item "
              "JOIN Owned_Item ON Owned_Item.item_id = Item.id "
              "WHERE Owned_Item.id = " << ownedItemId << ";";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            id = result->value(0).toULongLong();
        }
        delete result;
    }
    
    return id;
}

unsigned long long ItemModel::getItemPolicy(unsigned long long ownedItemId)
{
    unsigned long long policy = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT policy FROM Owned_Item WHERE id = " << ownedItemId << ";";
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            policy = result->value(0).toULongLong();
        }
        delete result;
    }
    
    return policy;
}

bool ItemModel::updateItemPolicy(unsigned long long ownedItemId, int policy)
{
    bool success = false;
    stringstream stream(stringstream::out);
    
    stream << "UPDATE Owned_Item SET policy = " << policy << " "
              "WHERE id = " << ownedItemId << ";";
    
    success = dbCon.nonQuery(stream.str());
    
    return success;
}

bool ItemModel::checkIfOwned(unsigned long long itemId, unsigned long long ownerId)
{
    bool itemOwned = false;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    
    stream << "SELECT id from Owned_Item WHERE member_id = " << ownerId
           << " and item_id = " << itemId << ";";
    
    result = dbCon.query(stream.str());
    if (result != 0) {
        if (result->next()) {
            itemOwned = true;
        }
        delete result;
    }
    
    return itemOwned;
}

bool ItemModel::linkToMember(unsigned long long itemId, unsigned long long ownerId)
{
    bool success = false;
    stringstream stream(stringstream::out);
    
    stream << "INSERT INTO Owned_Item (member_id, item_id, policy) "
              "VALUES (" << ownerId << ", " << itemId << ", 1);";
    
    success = dbCon.nonQuery(stream.str());
    
    return success;
}

OwnedItem * ItemModel::getOwners(unsigned long long itemId, unsigned long long memberId, int & numItems)
{
    OwnedItem * ownedItems = 0;
    OwnedItem * item = 0;
    Member * member = 0;
    QueryResult * result = 0;
    stringstream stream(stringstream::out);
    int index;
    
    stream << "SELECT Item.id, title, Genre.genre, Publisher.publisher, year, "
              "type, Owned_item.id AS owned_item_id, Member.id AS member_id, "
              "username, email, policy FROM Item "
              "JOIN Genre ON Item.genre = Genre.id "
              "JOIN Publisher ON Item.publisher = Publisher.id "
              "JOIN Owned_Item ON Owned_Item.item_id = Item.id "
              "JOIN Member ON Owned_Item.member_id = Member.id "
              "WHERE Item.id = " << itemId << " "
              "AND NOT Member.id = " << memberId << " "
              "AND policy != 3;";
              
    result = dbCon.query(stream.str());
    if (result != 0) {
        numItems = result->size();
        if (numItems > 0) {
            ownedItems = new OwnedItem[numItems];
        }
        if (ownedItems != 0) {
            index = 0;
            while (result->next()) {
                item = &ownedItems[index];
                item->setId(result->value(0).toULongLong());
                item->setTitle(result->value(1).toString().toAscii().data());
                item->setGenre(result->value(2).toString().toAscii().data());
                item->setPublisher(result->value(3).toString().toAscii().data());
                item->setYear(result->value(4).toUInt());
                item->setItemType(result->value(5).toULongLong());
                item->setOwnedItemId(result->value(6).toULongLong());
                member = new Member();
                member->setId(result->value(7).toULongLong());
                member->setUsername(result->value(8).toString().toAscii().data());
                member->setEmail(result->value(9).toString().toAscii().data());
                item->setOwner(member);
                item->setItemPolicy(result->value(10).toULongLong());
            }
        }
        delete result;
    }
    
    return ownedItems;
}

