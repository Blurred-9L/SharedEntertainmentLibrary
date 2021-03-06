#include "Movie.h"

Movie::Movie() :
    EntertainmentItem(), director(), mainActors(), duration(), rating(0)
{
}

Movie::Movie(const string & title, const string & genre,
             const string & publisher, unsigned year,
             const string & director, const QTime & duration,
             unsigned long long rating) :
    EntertainmentItem(title, genre, publisher, year), director(director),
    mainActors(), duration(duration.hour(), duration.minute(), duration.second()),
    rating(rating)
{
}

Movie::~Movie()
{
}

const string & Movie::getDirector() const
{
    return director;
}

const vector<string> & Movie::getMainActors() const
{
    return mainActors;
}

vector<string> & Movie::getMainActors()
{
    return mainActors;
}

const QTime & Movie::getDuration() const
{
    return duration;
}

QTime & Movie::getDuration()
{
    return duration;
}

unsigned long long Movie::getRating() const
{
    return rating;
}

void Movie::setDirector(const string & director)
{
    this->director = director;
}

void Movie::setMainActors(const vector<string> & mainActors)
{
    this->mainActors = mainActors;
}

void Movie::setDuration(const QTime & duration)
{
    this->duration.setHMS(duration.hour(), duration.minute(),
                          duration.second());
}

void Movie::setRating(unsigned long long rating)
{
    this->rating = rating;
}

string Movie::getRatingString(unsigned long long rating)
{
    string ratingString = "";
    
    switch (rating) {
    case RATING_MOVIE_R:
        ratingString = "Rating R";
        break;
    }
    
    return ratingString;
}
