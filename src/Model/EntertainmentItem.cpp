#include "EntertainmentItem.h"

/**
 *  @details
 */
EntertainmentItem::EntertainmentItem() :
    id(0), title(), genre(), publisher(), year()
{
}

/**
 *  @details
 */
EntertainmentItem::EntertainmentItem(const string & title, const string & genre,
                                     const string & publisher, unsigned year) :
    id(0), title(title), genre(genre), publisher(publisher), year(year)
{
}

/**
 *  @details
 */
EntertainmentItem::~EntertainmentItem()
{
}

/**
 *  @details
 */
unsigned EntertainmentItem::getId() const
{
    return id;
}

/**
 *  @details
 */
const string & EntertainmentItem::getTitle() const
{
    return title;
}

/**
 *  @details
 */
const string & EntertainmentItem::getGenre() const
{
    return genre;
}

/**
 *  @details
 */
const string & EntertainmentItem::getPublisher() const
{
    return publisher;
}

/**
 *  @details
 */
unsigned EntertainmentItem::getYear() const
{
    return year;
}

/**
 *  @details
 */
void EntertainmentItem::setId(unsigned id)
{
    this->id = id;
}

/**
 *  @details
 */
void EntertainmentItem::setTitle(const string & title)
{
    this->title = title;
}

/**
 *  @details
 */
void EntertainmentItem::setGenre(const string & genre)
{
    this->genre = genre;
}

/**
 *  @details
 */
void EntertainmentItem::setPublisher(const string & publisher)
{
    this->publisher = publisher;
}

/**
 *  @details
 */
void EntertainmentItem::setYear(unsigned year)
{
    this->year = year;
}
