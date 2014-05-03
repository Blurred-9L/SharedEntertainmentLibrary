#include "Videogame.h"

Videogame::Videogame() :
    EntertainmentItem(), esrbRating(0), platform(0)
{
}

Videogame::Videogame(const string & title, const string & genre,
                     const string & publisher, unsigned year,
                     unsigned esrbRating, unsigned platform) :
    EntertainmentItem(title, genre, publisher, year), esrbRating(esrbRating), platform(platform)
{
}

Videogame::~Videogame()
{
}

unsigned Videogame::getEsrbRating() const
{
    return esrbRating;
}

unsigned Videogame::getPlatform() const
{
    return platform;
}

void Videogame::setEsrbRating(unsigned esrbRating)
{
    this->esrbRating = esrbRating;
}

void Videogame::setPlatform(unsigned platform)
{
    this->platform = platform;
}

string Videogame::getRatingString(unsigned esrbRating)
{
    string ratingString = "";
    
    return ratingString;
}

string Videogame::getPlatformString(unsigned platform)
{
    string platformString = "";
    
    return platformString;
}

