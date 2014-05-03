#ifndef SEL_USER_LIBRARY_WIDGET_H
#define SEL_USER_LIBRARY_WIDGET_H

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
 *  @class  SELUserLibraryWidget
 */
class SELUserLibraryWidget : public QWidget {
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
    QPushButton * loanPolicyButton;
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
    SELUserLibraryWidget(QWidget * parent = 0);
    ///
    virtual ~SELUserLibraryWidget();
    
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
    ///
    void emitIdChangePolicy();
    
signals:
    ///
    void getUserLibraryPage(unsigned pageNumber);
    ///
    void getItemData(unsigned long long itemId);
    ///
    void changeItemLoanPolicy(unsigned long long itemId);
};

#endif /// Not SEL_USER_LIBRARY_WIDGET_H
