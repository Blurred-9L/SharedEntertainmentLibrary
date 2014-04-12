#ifndef MUSIC_ALBUM_H
#define MUSIC_ALBUM_H

#include "EntertainmentItem.h"

#include <vector>
using std::vector;

#include <QtCore/QTime>

/**
 *  @class  MusicAlbum
 */
class MusicAlbum : public EntertainmentItem {
private:
    ///
    string artist;
    ///
    vector<string> tracks;
    ///
    unsigned nTracks;
    ///
    QTime duration;
    
public:
    ///
    MusicAlbum();
    ///
    MusicAlbum(const string & title, const string & genre,
               const string & publisher, unsigned year, const string & artist,
               unsigned nTracks, const QTime & duration);
    ///
    virtual ~MusicAlbum();
    ///
    const string & getArtist() const;
    ///
    const vector<string> & getTracks() const;
    ///
    vector<string> & getTracks();
    ///
    unsigned getNTracks() const;
    ///
    const QTime & getDuration() const;
    ///
    QTime & getDuration();
    ///
    void setArtist(const string & artist);
    ///
    void setTracks(const vector<string> & tracks);
    ///
    void setNTracks(unsigned nTracks);
    ///
    void setDuration(const QTime & duration);
};

#endif /// Not MUSIC_ALBUM_H
