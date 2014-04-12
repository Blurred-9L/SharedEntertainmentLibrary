#ifndef MOVIE_H
#define MOVIE_H

#include "EntertainmentItem.h"

#include <vector>
using std::vector;

#include <QtCore/QTime>

/**
 *  @class  Movie
 */
class Movie : public EntertainmentItem {
private:
    ///
    string director;
    ///
    vector<string> mainActors;
    ///
    QTime duration;
    ///
    int rating;
    
public:
    /**
     *  @enum   MovieRating
     */
    enum MovieRating {
        RATING_INVALID = 0
    };
    
    ///
    Movie();
    ///
    Movie(const string & title, const string & genre, const string & publisher,
          unsigned year, const string & director, const QTime & duration,
          int rating);
    ///
    virtual ~Movie();
    ///
    const string & getDirector() const;
    ///
    const vector<string> & getMainActors() const;
    ///
    vector<string> & getMainActors();
    ///
    const QTime & getDuration() const;
    ///
    QTime & getDuration();
    ///
    int getRating() const;
    ///
    void setDirector(const string & director);
    ///
    void setMainActors(const vector<string> & mainActors);
    ///
    void setDuration(const QTime & duration);
    ///
    void setRating(int rating);
};

#endif /// Not MOVIE_H
