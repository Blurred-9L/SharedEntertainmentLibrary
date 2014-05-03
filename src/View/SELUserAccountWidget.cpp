#include "SELUserAccountWidget.h"

#include <QtGui/QTableWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtCore/QStringList>

const int SELUserAccountWidget::ROWS_PER_PAGE = 10;
const int SELUserAccountWidget::NUM_COLUMNS = 3;

///
const int WIDTH_OFFSET = 30;

SELUserAccountWidget::SELUserAccountWidget(QWidget * parent) :
    QWidget(parent), requestIds(0)
{
    QStringList headers;
    const char * headerContents[] = {"Date", "Member", "Status"};
    int tableWidth = 0;
    
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    QVBoxLayout * userLayout = new QVBoxLayout();
    QVBoxLayout * tableLayout = new QVBoxLayout();
    QHBoxLayout * tableButtonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(userLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(tableLayout);
    
    usernameLabel = new QLabel("Username:");
    userLayout->addWidget(usernameLabel);
    
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setReadOnly(true);
    userLayout->addWidget(usernameLineEdit);
    
    emailLabel = new QLabel("Email:");
    userLayout->addWidget(emailLabel);
    
    emailLineEdit = new QLineEdit();
    emailLineEdit->setReadOnly(true);
    userLayout->addWidget(emailLineEdit);
    
    updateDataButton = new QPushButton("Update data");
    userLayout->addWidget(updateDataButton);
    userLayout->addStretch();
    
    messageTableWidget = new QTableWidget(ROWS_PER_PAGE, NUM_COLUMNS);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        headers.push_back(headerContents[i]);
    }
    messageTableWidget->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        tableWidth += messageTableWidget->columnWidth(i);
    }
    messageTableWidget->setMinimumWidth(tableWidth + WIDTH_OFFSET);
    tableLayout->addWidget(messageTableWidget);
    
    tableLayout->addLayout(tableButtonLayout);
    
    previousPageButton = new QPushButton("Previous");
    tableButtonLayout->addWidget(previousPageButton);
    
    currentPageLabel = new QLabel();
    currentPageLabel->setNum(1);
    currentPageLabel->setAlignment(Qt::AlignCenter);
    tableButtonLayout->addWidget(currentPageLabel);
    
    nextPageButton = new QPushButton("Next");
    tableButtonLayout->addWidget(nextPageButton);
    
    requestIds = new unsigned long long[ROWS_PER_PAGE];
    for (int i = 0; i < ROWS_PER_PAGE; i++) {
        requestIds[i] = 0;
    }
    
    /// Signals needed
    /// Pressed previous page button -> load previous table page.
    /// Pressed next page button -> load next table page.
    /// Double clicked item on table -> show item details dialog.
}

SELUserAccountWidget::~SELUserAccountWidget()
{
    if (requestIds != 0) {
        delete [] requestIds;
    }
}
