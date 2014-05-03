#ifndef ENTERTAINMENT_ITEM_H
#define ENTERTAINMENT_ITEM_H

#include <string>
using std::string;

/**
 *  @class  EntertainmentItem
 */
class EntertainmentItem {
private:
    ///
    unsigned long long id;
    ///
    string title;
    ///
    string genre;
    ///
    string publisher;
    ///
    unsigned year;
    
public:
    ///
    EntertainmentItem();
    ///
    EntertainmentItem(const string & title, const string & genre,
                      const string & publisher, unsigned year);
    ///
    virtual ~EntertainmentItem();
    ///
    unsigned long long getId() const;
    ///
    const string & getTitle() const;
    ///
    const string & getGenre() const;
    ///
    const string & getPublisher() const;
    ///
    unsigned getYear() const;
    ///
    void setId(unsigned long long id);
    ///
    void setTitle(const string & title);
    ///
    void setGenre(const string & genre);
    ///
    void setPublisher(const string & publisher);
    ///
    void setYear(unsigned year);
};

#endif /// Not ENTERTAINMENT_ITEM_H
