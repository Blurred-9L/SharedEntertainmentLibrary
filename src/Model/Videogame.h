#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "EntertainmentItem.h"

/**
 *  @class  Videogame
 */
class Videogame : public EntertainmentItem {
private:
    ///
    unsigned esrbRating;
    ///
    unsigned platform;
    
public:
    /**
     *  @enum   ESRBRating
     */
    enum ESRBRating {
        RATING_INVALID = 0
    };
    
    /**
     *  @enum   GamePlatform
     */
    enum GamePlatform {
        GAME_PLATFORM_INVALID = 0
    };
    
    ///
    Videogame();
    ///
    Videogame(const string & title, const string & genre,
              const string & publisher, unsigned year, unsigned esrbRating,
              unsigned platform);
    ///
    virtual ~Videogame();
    ///
    unsigned getEsrbRating() const;
    ///
    unsigned getPlatform() const;
    ///
    void setEsrbRating(unsigned esrbRating);
    ///
    void setPlatform(unsigned platform);
    
    ///
    static string getRatingString(unsigned esrbRating);
    ///
    static string getPlatformString(unsigned platform);
};

#endif /// Not VIDEOGAME_H
