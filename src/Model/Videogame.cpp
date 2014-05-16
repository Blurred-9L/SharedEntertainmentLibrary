#include "Videogame.h"

Videogame::Videogame() :
    EntertainmentItem(), esrbRating(0), platform(0)
{
}

Videogame::Videogame(const string & title, const string & genre,
                     const string & publisher, unsigned year,
                     unsigned long long esrbRating,
                     unsigned long long platform) :
    EntertainmentItem(title, genre, publisher, year), esrbRating(esrbRating), platform(platform)
{
}

Videogame::~Videogame()
{
}

unsigned long long Videogame::getEsrbRating() const
{
    return esrbRating;
}

unsigned long long Videogame::getPlatform() const
{
    return platform;
}

void Videogame::setEsrbRating(unsigned long long esrbRating)
{
    this->esrbRating = esrbRating;
}

void Videogame::setPlatform(unsigned long long platform)
{
    this->platform = platform;
}

string Videogame::getRatingString(unsigned long long esrbRating)
{
    string ratingString = "";
    
    switch (esrbRating) {
    case RATING_EVERYONE:
        ratingString = "Everyone";
        break;
    case RATING_EVERYONE_10:
        ratingString = "Everyone 10+";
        break;
    case RATING_TEEN:
        ratingString = "Teen";
        break;
    case RATING_MATURE:
        ratingString = "Mature";
        break;
    }
    
    return ratingString;
}

string Videogame::getPlatformString(unsigned long long platform)
{
    string platformString = "";
    
    switch (platform) {
    case GAME_PLATFORM_3DS:
        platformString = "Nintendo 3DS";
        break;
    case GAME_PLATFORM_DS:
        platformString = "Nintendo DS";
        break;
    }
    
    return platformString;
}

