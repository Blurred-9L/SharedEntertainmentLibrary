#include "SELMainLibraryWidget.h"

#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

///
const unsigned SELMainLibraryWidget::ITEMS_PER_PAGE = 20;

SELMainLibraryWidget::SELMainLibraryWidget(QWidget * parent) :
    QWidget(parent), itemIds(0)
{
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    QVBoxLayout * infoLayout = new QVBoxLayout();
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
    /// Next page button pressed -> currentPageLabel + 1
    /// Next page button pressed -> loadNextPage
    /// Previous page button pressed -> currentPageLabel - 1
    /// Previous page button pressed -> loadPreviousPage
    /// Item on list selected -> updateInfoLabels
}

SELMainLibraryWidget::~SELMainLibraryWidget()
{
    if (itemIds != 0) {
        delete [] itemIds;
    }
}
