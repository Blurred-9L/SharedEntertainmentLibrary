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

class EntertainmentItem;

/**
 *  @class  SELMainLibraryWidget
 */
class SELMainLibraryWidget : public QWidget {
Q_OBJECT

private:
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
    unsigned long long * itemIds;
    
    ///
    void replaceLabelText(const QString & text, int index);
    ///
    unsigned long long findId(QListWidgetItem * item);

public:
    ///
    static const unsigned ITEMS_PER_PAGE;

    ///
    SELMainLibraryWidget(QWidget * parent = 0);
    ///
    virtual ~SELMainLibraryWidget();
    
public slots:
    ///
    void updateItemInfo(EntertainmentItem & item, unsigned long long type);
    ///
    void updateItemPage(EntertainmentItem ** items, unsigned numItems);
    
private slots:
    ///
    void updatePageIndexNext();
    ///
    void updatePageIndexPrevious();
    ///
    void emitIdGetData(QListWidgetItem * item);
    
signals:
    ///
    void getMainLibraryPage(unsigned pageNumber);
    ///
    void getItemData(unsigned long long itemId);
};

#endif /// Not SEL_MAIN_LIBRARY_WIDGET_H
