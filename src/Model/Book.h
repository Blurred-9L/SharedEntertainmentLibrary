#ifndef BOOK_H
#define BOOK_H

#include "EntertainmentItem.h"

#include <vector>
using std::vector;

/**
 *  @class  Book
 */
class Book : public EntertainmentItem {
private:
    ///
    string isbn;
    ///
    vector<string> authors;
    ///
    unsigned nPages;
    
public:
    ///
    Book();
    ///
    Book(const string & title, const string & genre, const string & publisher,
         unsigned year, const string & isbn, unsigned nPages);
    ///
    virtual ~Book();
    ///
    const string & getIsbn() const;
    ///
    const vector<string> & getAuthors() const;
    ///
    vector<string> & getAuthors();
    ///
    unsigned getNPages() const;
    ///
    void setIsbn(const string & isbn);
    ///
    void setAuthors(const vector<string> & authors);
    ///
    void setNPages(unsigned nPages);
};

#endif /// Not BOOK_H
