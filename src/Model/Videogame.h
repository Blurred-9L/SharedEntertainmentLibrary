#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "EntertainmentItem.h"

/**
 *  @class  Videogame
 */
class Videogame : public EntertainmentItem {
private:
    ///
    unsigned long long esrbRating;
    ///
    unsigned long long platform;
    
public:
    /**
     *  @enum   ESRBRating
     */
    enum ESRBRating {
        RATING_INVALID = 0,
        RATING_EVERYONE = 1
    };
    
    /**
     *  @enum   GamePlatform
     */
    enum GamePlatform {
        GAME_PLATFORM_INVALID = 0,
        GAME_PLATFORM_3DS = 1,
    };
    
    ///
    Videogame();
    ///
    Videogame(const string & title, const string & genre,
              const string & publisher, unsigned year,
              unsigned long long esrbRating,
              unsigned long long platform);
    ///
    virtual ~Videogame();
    ///
    unsigned long long getEsrbRating() const;
    ///
    unsigned long long getPlatform() const;
    ///
    void setEsrbRating(unsigned long long esrbRating);
    ///
    void setPlatform(unsigned long long platform);
    
    ///
    static string getRatingString(unsigned long long esrbRating);
    ///
    static string getPlatformString(unsigned long long platform);
};

#endif /// Not VIDEOGAME_H
