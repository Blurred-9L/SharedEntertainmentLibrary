#include "MusicAlbum.h"

MusicAlbum::MusicAlbum() :
    EntertainmentItem(), artist(), tracks(), nTracks(0), duration()
{
}

MusicAlbum::MusicAlbum(const string & title, const string & genre,
                       const string & publisher, unsigned year,
                       const string & artist, unsigned nTracks,
                       const QTime & duration) :
    EntertainmentItem(title, genre, publisher, year), artist(artist),
    tracks(), nTracks(nTracks), duration(duration.hour(), duration.minute(),
    duration.second())
{
}

MusicAlbum::~MusicAlbum()
{
}

const string & MusicAlbum::getArtist() const
{
    return artist;
}

const vector<string> & MusicAlbum::getTracks() const
{
    return tracks;
}

vector<string> & MusicAlbum::getTracks()
{
    return tracks;
}

unsigned MusicAlbum::getNTracks() const
{
    return nTracks;
}

const QTime & MusicAlbum::getDuration() const
{
    return duration;
}

QTime & MusicAlbum::getDuration()
{
    return duration;
}

void MusicAlbum::setArtist(const string & artist)
{
    this->artist = artist;
}

void MusicAlbum::setTracks(const vector<string> & tracks)
{
    this->tracks = tracks;
}

void MusicAlbum::setNTracks(unsigned nTracks)
{
    this->nTracks = nTracks;
}

void MusicAlbum::setDuration(const QTime & duration)
{
    this->duration.setHMS(duration.hour(), duration.minute(),
                          duration.second());
}
