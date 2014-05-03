#include "SELUserAccountWidget.h"
#include "../Model/LoanRequest.h"
#include "../Model/OwnedItem.h"
#include "../Model/Member.h"
#include "../Model/Error.h"

#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
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
    /// Pressed previous page button, load previous table page.
    connect(previousPageButton, SIGNAL(clicked()),
            this, SLOT(updatePageIndexPrevious()));
    /// Pressed next page button, load next table page.
    connect(nextPageButton, SIGNAL(clicked()),
            this, SLOT(updatePageIndexNext()));
    /// Double clicked item on table, show item details dialog.
    connect(messageTableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)),
            this, SLOT(emitIdShowData(QTableWidgetItem *)));
}

SELUserAccountWidget::~SELUserAccountWidget()
{
    if (requestIds != 0) {
        delete [] requestIds;
    }
}

void SELUserAccountWidget::updateMessagesTable(LoanRequest ** requests, unsigned numRequests)
{
    unsigned i;
    
    for (i = 0; i < numRequests; i++) {
        messageTableWidget->item(i, 0)->setText(requests[i]->getStartDate().toString("dd/MM/yyyy"));
        messageTableWidget->item(i, 1)->setText(requests[i]->getRequestedItem().getOwner().getUsername().c_str());
        messageTableWidget->item(i, 2)->setText(LoanRequest::getRequestStatusString(requests[i]->getRequestStatus()).c_str());
    }
    
    while (i < (unsigned)ROWS_PER_PAGE) {
        messageTableWidget->item(i, 0)->setText("");
        messageTableWidget->item(i, 1)->setText("");
        messageTableWidget->item(i, 2)->setText("");
        i++;
    }
}

/////////////
// Private //
/////////////

void SELUserAccountWidget::updatePageIndexNext()
{
    int pageToGet;
    bool ok;
    
    pageToGet = currentPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet++;
        emit getUserMessagesPage(pageToGet);
        currentPageLabel->setNum(pageToGet);
    }
}

void SELUserAccountWidget::updatePageIndexPrevious()
{
    int pageToGet;
    bool ok;
    
    pageToGet = currentPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet--;
        if (pageToGet > 0) {
            emit getUserMessagesPage(pageToGet);
            currentPageLabel->setNum(pageToGet);
        }
    }
}

void SELUserAccountWidget::emitIdShowData(QTableWidgetItem * item)
{
    unsigned long long id = findId(item);
    
    if (id > 0) {
        emit showRequestReplyDialog(id);
    } else {
        Error::raiseError(Error::ERROR_REQ_ID_NOT_FOUND);
    }
}

unsigned long long SELUserAccountWidget::findId(QTableWidgetItem * item)
{
    int i, j, row;
    bool found = false;
    unsigned long long foundId;
    
    for (i = 0; i < ROWS_PER_PAGE && !found; i++) {
        for (j = 0; j < NUM_COLUMNS && found; j++) {
            if (item == messageTableWidget->item(i, j)) {
                row = i;
                found = true;
            }
        }
    }
    
    if (found) {
        foundId = requestIds[row];
    } else {
        foundId = 0;
    }
    
    return foundId;
}

