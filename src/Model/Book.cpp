#include "Book.h"

Book::Book() :
    EntertainmentItem(), isbn(), authors(), nPages(0)
{
}

Book::Book(const string & title, const string & genre,
           const string & publisher, unsigned year, const string & isbn,
           unsigned nPages) :
    EntertainmentItem(title, genre, publisher, year), isbn(isbn),
    authors(), nPages(nPages)
{
}

Book::~Book()
{
}

const string & Book::getIsbn() const
{
    return isbn;
}

const vector<string> & Book::getAuthors() const
{
    return authors;
}

vector<string> & Book::getAuthors()
{
    return authors;
}

void Book::setIsbn(const string & isbn)
{
    this->isbn = isbn;
}

void Book::setAuthors(const vector<string> & authors)
{
    this->authors = authors;
}

void Book::setNPages(int nPages)
{
    if (nPages >= 0) {
        this->nPages = nPages;
    }
}
