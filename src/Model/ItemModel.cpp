#include "ItemModel.h"
#include "EntertainmentItem.h"
#include "Book.h"
#include "Movie.h"
#include "MusicAlbum.h"
#include "Videogame.h"
#include "Error.h"
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
    
    stream << "SELECT Item.id, title, Genre.genre, publisher, year FROM Item "
              "JOIN Genre on Item.genre = Genre.id "
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

EntertainmentItem * ItemModel::getItem(unsigned long long id, unsigned long long & itemType)
{
    EntertainmentItem * item = 0;
    
    itemType = getItemType(id);
    switch (itemType) {
    case 1:
        item = getBookItem(id);
        break;
    case 2:
        item = getMovieItem(id);
        break;
    case 3:
        item = getMusicItem(id);
        break;
    case 4:
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

