#ifndef SEL_MAIN_LIBRARY_WIDGET_H
#define SEL_MAIN_LIBRARY_WIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QList>

class QListWidget;
class QLabel;
class QPushButton;

/**
 *  @class  SELMainLibraryWidget
 */
class SELMainLibraryWidget : public QWidget {
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
    unsigned long long * itemIds;
    
    ///
    static const unsigned ITEMS_PER_PAGE;

public:
    ///
    SELMainLibraryWidget(QWidget * parent = 0);
    ///
    virtual ~SELMainLibraryWidget();
};

#endif /// Not SEL_MAIN_LIBRARY_WIDGET_H
