#ifndef SEL_MAIN_LIBRARY_WIDGET_H
#define SEL_MAIN_LIBRARY_WIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QList>

class QVBoxLayout;
class QListWidget;
class QLabel;
class QPushButton;
class QListWidgetItem;
class QString;

class SELController;
class EntertainmentItem;
class OwnedItem;

/**
 *  @class  SELMainLibraryWidget
 */
class SELMainLibraryWidget : public QWidget {
Q_OBJECT

private:
    ///
    SELController & controller;
    ///
    QVBoxLayout * infoLayout;
    ///
    QListWidget * libraryListWidget;
    ///
    QList<QLabel *> itemInfo;
    ///
    QLabel * currentPageLabel;
    ///
    QPushButton * previousPageButton;
    ///
    QPushButton * nextPageButton;
    ///
    QPushButton * addToLibraryButton;
    ///
    QPushButton * requestButton;
    ///
    unsigned long long * itemIds;
    ///
    bool userLibraryChanged;
    ///
    bool userRequestsChanged;
    
    ///
    unsigned long long findId(QListWidgetItem * item);
    ///
    void replaceLabelText(const QString & text, int index);
    ///
    void showAddItemConfirmDialog(EntertainmentItem * item);

public:
    ///
    static const unsigned ITEMS_PER_PAGE;

    ///
    SELMainLibraryWidget(SELController & controller, QWidget * parent = 0);
    ///
    virtual ~SELMainLibraryWidget();
    ///
    bool checkUserLibraryChanged();
    ///
    void setUserLibraryChanged(bool changed);
    ///
    bool checkUserRequestsChanged();
    ///
    void setUserRequestsChanged(bool changed);
    
public slots:
    ///
    void updateItemInfo(EntertainmentItem & item, unsigned long long type);
    ///
    void updateItemPage(EntertainmentItem * items, unsigned numItems);
    ///
    void tryAddToLibrary();
    
private slots:
    ///
    void updatePageIndexNext();
    ///
    void updatePageIndexPrevious();
    ///
    void emitIdGetData(QListWidgetItem * item);
    ///
    void setupRequestDialog();
    ///
    void showRequestDialog(unsigned long long id, OwnedItem * items, int numItems);
    ///
    void tryToLoanItem(OwnedItem & item);
    
signals:
    ///
    void getMainLibraryPage(unsigned pageNumber);
    ///
    void getItemData(unsigned long long itemId);
};

#endif /// Not SEL_MAIN_LIBRARY_WIDGET_H
