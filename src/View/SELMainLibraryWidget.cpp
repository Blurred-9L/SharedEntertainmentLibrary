#include "SELMainLibraryWidget.h"
#include "../Model/Book.h"
#include "../Model/Movie.h"
#include "../Model/MusicAlbum.h"
#include "../Model/Videogame.h"
#include "../Model/Error.h"
#include "../Controller/SELController.h"

#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

///
const unsigned SELMainLibraryWidget::ITEMS_PER_PAGE = 20;

SELMainLibraryWidget::SELMainLibraryWidget(SELController & controller, QWidget * parent) :
    QWidget(parent), controller(controller), itemIds(0)
{
    EntertainmentItem * items;
    int numItems;
    
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    infoLayout = new QVBoxLayout();
    QVBoxLayout * listLayout = new QVBoxLayout();
    QHBoxLayout * listButtonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(listLayout);
    
    itemInfo.append(new QLabel("Title"));
    itemInfo.append(new QLabel("Genre"));
    itemInfo.append(new QLabel("Publisher"));
    itemInfo.append(new QLabel("Year"));
    for (QList<QLabel *>::iterator i = itemInfo.begin(); i != itemInfo.end(); i++) {
        infoLayout->addWidget(*i);
    }
    infoLayout->addStretch();
    
    libraryListWidget = new QListWidget();
    itemIds = new unsigned long long[ITEMS_PER_PAGE];
    for (unsigned i = 0; i < ITEMS_PER_PAGE; i++) {
        itemIds[i] = 0;
    }
    listLayout->addWidget(libraryListWidget);
    
    listLayout->addLayout(listButtonLayout);
    
    previousPageButton = new QPushButton("Previous");
    listButtonLayout->addWidget(previousPageButton);
    
    currentPageLabel = new QLabel();
    currentPageLabel->setNum(1);
    currentPageLabel->setAlignment(Qt::AlignCenter);
    listButtonLayout->addWidget(currentPageLabel);
    
    nextPageButton = new QPushButton("Next");
    listButtonLayout->addWidget(nextPageButton);
    
    /// Signals needed:
    /// Next page button pressed, updates label and loads next page.
    connect(nextPageButton, SIGNAL(clicked()),
            this, SLOT(updatePageIndexNext()));
    /// Previous page button pressed, updates label and loads previous page.
    connect(previousPageButton, SIGNAL(clicked()),
            this, SLOT(updatePageIndexPrevious()));
    /// Item on list selected -> updateInfoLabels
    connect(libraryListWidget, SIGNAL(itemClicked(QListWidgetItem *)),
            this, SLOT(emitIdGetData(QListWidgetItem *)));
            
    /// Loads first page of items.
    items = controller.retrieveLibraryPage(1, numItems);
    updateItemPage(items, (unsigned)numItems);
}

SELMainLibraryWidget::~SELMainLibraryWidget()
{
    if (itemIds != 0) {
        delete [] itemIds;
    }
}

void SELMainLibraryWidget::updateItemInfo(EntertainmentItem & item,
                                          unsigned long long type)
{
    Book * bookItem = 0;
    Movie * movieItem = 0;
    MusicAlbum * musicItem = 0;
    Videogame * videogameItem = 0;
    int currentIndex = 4;
    unsigned size;

    /// Update title
    replaceLabelText(item.getTitle().c_str(), 0);
    /// Update genre
    replaceLabelText(item.getGenre().c_str(), 1);
    /// Update publisher
    replaceLabelText(item.getPublisher().c_str(), 2);
    /// Update year
    replaceLabelText(QString::number(item.getYear()), 3);
    
    /// Check type to write extra data.
    switch (type) {
    case 1:
        bookItem = dynamic_cast<Book *>(&item);
        if (bookItem != 0) {
            /// Write book data
            replaceLabelText("ISBN:", currentIndex++);
            replaceLabelText(bookItem->getIsbn().c_str(), currentIndex++);
            replaceLabelText("Authors:", currentIndex++);
            size = bookItem->getAuthors().size();
            for (unsigned i = 0; i < size; i++) {
                replaceLabelText(bookItem->getAuthors()[i].c_str(), currentIndex++);
            }
            replaceLabelText("Num pages", currentIndex++);
            replaceLabelText(QString::number(bookItem->getNPages()), currentIndex++);
        }
        break;
    case 2:
        movieItem = dynamic_cast<Movie *>(&item);
        if (movieItem != 0) {
            /// Write movie data
            replaceLabelText("Director:", currentIndex++);
            replaceLabelText(movieItem->getDirector().c_str(), currentIndex++);
            replaceLabelText("Actors:", currentIndex++);
            size = movieItem->getMainActors().size();
            for (unsigned i = 0; i < size; i++) {
                replaceLabelText(movieItem->getMainActors()[i].c_str(), currentIndex++);
            }
            replaceLabelText("Rating:", currentIndex++);
            replaceLabelText(Movie::getRatingString(movieItem->getRating()).c_str(), currentIndex++);
        }
        break;
    case 3:
        musicItem = dynamic_cast<MusicAlbum *>(&item);
        if (musicItem != 0) {
            /// Write music data
            replaceLabelText("Artist:", currentIndex++);
            replaceLabelText(musicItem->getArtist().c_str(), currentIndex++);
            replaceLabelText("Num tracks:", currentIndex++);
            replaceLabelText(QString::number(musicItem->getNTracks()), currentIndex++);
            replaceLabelText("Total duration:", currentIndex++);
            replaceLabelText(musicItem->getDuration().toString("hh:mm:ss"), currentIndex++);
        }
        break;
    case 4:
        videogameItem = dynamic_cast<Videogame *>(&item);
        if (videogameItem != 0) {
            replaceLabelText("Rating:", currentIndex++);
            replaceLabelText(Videogame::getRatingString(videogameItem->getEsrbRating()).c_str(), currentIndex++);
            replaceLabelText("Platform:", currentIndex++);
            replaceLabelText(Videogame::getPlatformString(videogameItem->getPlatform()).c_str(), currentIndex++);
        }
        break;
    default:
        Error::raiseError(Error::ERROR_UNKNOWN_ITEM_TYPE);
        break;
    }

    size = itemInfo.size();
    while (currentIndex < (int)size) {
        itemInfo[currentIndex++]->setText("");
    }
}

void SELMainLibraryWidget::updateItemPage(EntertainmentItem * items,
                                          unsigned numItems)
{
    QList<QListWidgetItem *> listItems = libraryListWidget->findItems("*", Qt::MatchWildcard);
    QListWidgetItem * removedItem = 0;
    unsigned i, size = listItems.size();
    
    for (i = 0; i < numItems; i++) {
        if (i >= size) {
            libraryListWidget->addItem(new QListWidgetItem());
        }
        libraryListWidget->item(i)->setText(items[i].getTitle().c_str());
        itemIds[i] = items[i].getId();
    }
    
    /// If less items were obtained than there previously were:
    while (i < size) {
        removedItem = libraryListWidget->takeItem(i);
        if (removedItem != 0) {
            delete removedItem;
        }
        i++;
    }
    delete [] items;
}

/////////////
// Private //
/////////////

void SELMainLibraryWidget::updatePageIndexNext()
{
    EntertainmentItem * items = 0;
    int numItems;
    int pageToGet;
    bool ok;
    
    pageToGet = currentPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet++;
        items = controller.retrieveLibraryPage(pageToGet, numItems);
        if ((items != 0) && (numItems > 0)) {
            currentPageLabel->setNum(pageToGet);
            updateItemPage(items, (unsigned)numItems);
        }
    } else {
        Error::raiseError(Error::ERROR_NO_SUCH_PAGE_MLIB);
    }
}

void SELMainLibraryWidget::updatePageIndexPrevious()
{
    EntertainmentItem * items = 0;
    int numItems;
    int pageToGet;
    bool ok;
    
    pageToGet = currentPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet--;
        if (pageToGet > 0) {
            items = controller.retrieveLibraryPage(pageToGet, numItems);
            if ((items != 0) && (numItems > 0)) {
                currentPageLabel->setNum(pageToGet);
                updateItemPage(items, (unsigned)numItems);
            }
        }
    } else {
        Error::raiseError(Error::ERROR_NO_SUCH_PAGE_MLIB);
    }
}

void SELMainLibraryWidget::emitIdGetData(QListWidgetItem * item)
{
    EntertainmentItem * eItem;
    unsigned long long id = findId(item);
    unsigned long long itemType;
    
    if (id > 0) {
        eItem = controller.retrieveItem(id, itemType);
        updateItemInfo(*eItem, itemType);
    } else {
        Error::raiseError(Error::ERROR_ITEM_ID_NOT_FOUND);
    }
}

unsigned long long SELMainLibraryWidget::findId(QListWidgetItem * item)
{
    QList<QListWidgetItem *> items = libraryListWidget->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem *>::iterator i;
    bool found = false;
    unsigned index = 0;
    unsigned long long id;
    
    for (i = items.begin(); i != items.end() && !found; i++) {
        if ((*i) == item) {
            found = true;
        } else {
            index++;
        }
    }
    
    if (found) {
        id = itemIds[index];
    } else {
        id = 0;
    }
    
    return id;
}

void SELMainLibraryWidget::replaceLabelText(const QString & text, int index)
{
    if (index >= itemInfo.size()) {
        itemInfo.append(new QLabel(text));
        infoLayout->addWidget(itemInfo[index]);
    } else {
        itemInfo[index]->setText(text);
    }
}

