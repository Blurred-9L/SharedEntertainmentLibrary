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
    unsigned long long rating;
    
public:
    /**
     *  @enum   MovieRating
     */
    enum MovieRating {
        RATING_INVALID = 0,
        RATING_MOVIE_R = 2
    };
    
    ///
    Movie();
    ///
    Movie(const string & title, const string & genre, const string & publisher,
          unsigned year, const string & director, const QTime & duration,
          unsigned long long rating);
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
    unsigned long long getRating() const;
    ///
    void setDirector(const string & director);
    ///
    void setMainActors(const vector<string> & mainActors);
    ///
    void setDuration(const QTime & duration);
    ///
    void setRating(unsigned long long rating);
    
    ///
    static string getRatingString(unsigned long long rating);
};

#endif /// Not MOVIE_H
