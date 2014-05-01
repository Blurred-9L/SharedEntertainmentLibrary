#ifndef SEL_USER_LIBRARY_WIDGET_H
#define SEL_USER_LIBRARY_WIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QList>

class QListWidget;
class QLabel;
class QPushButton;

/**
 *  @class  SELUserLibraryWidget
 */
class SELUserLibraryWidget : public QWidget {
private:
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
    static const unsigned ITEMS_PER_PAGE;
    
public:
    ///
    SELUserLibraryWidget(QWidget * parent = 0);
    ///
    virtual ~SELUserLibraryWidget();
};

#endif /// Not SEL_USER_LIBRARY_WIDGET_H
