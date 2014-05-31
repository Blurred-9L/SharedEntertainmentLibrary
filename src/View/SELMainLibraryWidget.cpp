#include "SELMainLibraryWidget.h"
#include "SELRequestDialog.h"
#include "../Model/Book.h"
#include "../Model/Movie.h"
#include "../Model/MusicAlbum.h"
#include "../Model/Videogame.h"
#include "../Model/OwnedItem.h"
#include "../Model/Error.h"
#include "../Controller/SELController.h"

#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMessageBox>

///
const unsigned SELMainLibraryWidget::ITEMS_PER_PAGE = 20;

SELMainLibraryWidget::SELMainLibraryWidget(SELController & controller, QWidget * parent) :
    QWidget(parent), controller(controller), itemIds(0), userLibraryChanged(false)
{
    EntertainmentItem * items;
    int numItems;
    
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    QVBoxLayout * mainInfoLayout = new QVBoxLayout();
    infoLayout = new QVBoxLayout();
    QVBoxLayout * listLayout = new QVBoxLayout();
    QHBoxLayout * listButtonLayout = new QHBoxLayout();
    QVBoxLayout * buttonLayout = new QVBoxLayout();
    
    mainLayout->addLayout(mainInfoLayout);
    mainLayout->addLayout(listLayout);
    
    mainInfoLayout->addLayout(infoLayout);
    mainInfoLayout->addLayout(buttonLayout);
    
    itemInfo.append(new QLabel("Title"));
    itemInfo.append(new QLabel("Genre"));
    itemInfo.append(new QLabel("Publisher"));
    itemInfo.append(new QLabel("Year"));
    for (QList<QLabel *>::iterator i = itemInfo.begin(); i != itemInfo.end(); i++) {
        infoLayout->addWidget(*i);
    }
    infoLayout->addStretch();
    
    addToLibraryButton = new QPushButton("Add to library");
    buttonLayout->addWidget(addToLibraryButton);
    
    requestButton = new QPushButton("Request loan");
    buttonLayout->addWidget(requestButton);
    
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
    /// Add to library button pressed -> try to add selected item to library.
    connect(addToLibraryButton, SIGNAL(clicked()),
            this, SLOT(tryAddToLibrary()));
    /// Request loan button pressed -> try to request a loan.
    connect(requestButton, SIGNAL(clicked()),
            this, SLOT(setupRequestDialog()));
            
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

bool SELMainLibraryWidget::checkUserLibraryChanged()
{
    return userLibraryChanged;
}

void SELMainLibraryWidget::setUserLibraryChanged(bool changed)
{
    userLibraryChanged = changed;
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
    unsigned i, size = listItems.size(), indexOffset;
    
    for (i = 0; i < numItems; i++) {
        if (i >= size) {
            libraryListWidget->addItem(new QListWidgetItem());
        }
        libraryListWidget->item(i)->setText(items[i].getTitle().c_str());
        itemIds[i] = items[i].getId();
    }
    
    /// If less items were obtained than there previously were:
    indexOffset = 0;
    while (i < size) {
        removedItem = libraryListWidget->takeItem(i - indexOffset);
        if (removedItem != 0) {
            delete removedItem;
            removedItem = 0;
        }
        itemIds[i] = 0;
        i++;
        indexOffset++;
    }
    
    delete [] items;
}

void SELMainLibraryWidget::tryAddToLibrary()
{
    QList<QListWidgetItem *> selectedItems = libraryListWidget->selectedItems();
    EntertainmentItem * item;
    unsigned long long id, itemType;
    int size = selectedItems.size();
    
    if (size == 1) {
        id = findId(selectedItems[0]);
        item = controller.retrieveItem(id, itemType);
        if (item != 0) {
            showAddItemConfirmDialog(item);
            delete item;
        }
    } else if (size > 1) {
        Error::raiseError(Error::ERROR_ITEM_SELECTION_ERROR);
    } else {
        Error::raiseError(Error::ERROR_NO_ITEM_SELECTED);
    }
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
    unsigned long long id;
    unsigned long long itemType;
    
    id = findId(item);
    if (id > 0) {
        eItem = controller.retrieveItem(id, itemType);
        if (eItem != 0) {
            updateItemInfo(*eItem, itemType);
            delete eItem;
        }
    } else {
        Error::raiseError(Error::ERROR_ITEM_ID_NOT_FOUND);
    }
}

void SELMainLibraryWidget::setupRequestDialog()
{
    QList<QListWidgetItem *> selectedItems = libraryListWidget->selectedItems();
    OwnedItem * items = 0;
    unsigned long long id;
    int numItems, size = selectedItems.size();
    
    if (size == 1) {
        id = findId(selectedItems[0]);
        items = controller.retrieveOwners(id, numItems);
        if (items != 0) {
            showRequestDialog(id, items, numItems);
            delete [] items;
        } else if (numItems == 0) {
            Error::raiseError(Error::ERROR_NO_USER_OWNS);
        }
    } else if (size > 1) {
        Error::raiseError(Error::ERROR_ITEM_SELECTION_ERROR);
    } else {
        Error::raiseError(Error::ERROR_NO_ITEM_SELECTED);
    }
}

void SELMainLibraryWidget::showRequestDialog(unsigned long long id, OwnedItem * items, int numItems)
{
    SELRequestDialog * dialog = 0;
    int result;
    bool userOwns = false;
    
    userOwns = controller.checkUserOwnsItem(id);
    if (!userOwns) {
        dialog = new SELRequestDialog(id, items, numItems);
        result = dialog->exec();
        if (result >= 0) {
            tryToLoanItem(items[result]);
        }
        delete dialog;
    } else {
        Error::raiseError(Error::ERROR_ITEM_ALREADY_OWNED);
    }
}

void SELMainLibraryWidget::tryToLoanItem(OwnedItem & item)
{
    switch (item.getItemPolicy()) {
    case OwnedItem::POLICY_FREE:
        controller.scheduleAutomaticLoan(item);
        break;
    case OwnedItem::POLICY_USER:
        /// show member message dialog
        /// make user select start date, duration 
        break;
    case OwnedItem::POLICY_NO_LOAN:
        Error::raiseError(Error::ERROR_ITEM_NO_LOAN);
        break;
    default:
        Error::raiseError(Error::ERROR_ITEM_INVALID_POLICY);
        break;
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

void SELMainLibraryWidget::showAddItemConfirmDialog(EntertainmentItem * item)
{
    QMessageBox confirmDialog(QMessageBox::Question, "Add to Library?", "",
                              QMessageBox::Ok | QMessageBox::Cancel, this);
    QString dialogText;
    bool itemOwned = controller.checkUserOwnsItem(item->getId());
    bool success;
    int dialogResult;
    
    if (!itemOwned) {
        dialogText = "Add the selected item (";
        dialogText += item->getTitle().c_str();
        dialogText += ") to your library?";
        confirmDialog.setText(dialogText);
        confirmDialog.setDefaultButton(QMessageBox::Ok);
        dialogResult = confirmDialog.exec();
        if (dialogResult == QMessageBox::Ok) {
            success = controller.addItemToUserLibrary(item->getId());
            if (success) {
                QMessageBox::information(this, "Success!", "Item added");
                userLibraryChanged = true;
            } else {
                Error::raiseError(Error::ERROR_ITEM_ADD_FAIL);
            }
        }
    } else {
        Error::raiseError(Error::ERROR_ITEM_OWNED);
    }
}

