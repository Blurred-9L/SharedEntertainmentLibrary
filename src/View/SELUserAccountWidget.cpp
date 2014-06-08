#include "SELUserAccountWidget.h"
#include "../Model/LoanRequest.h"
#include "../Model/OwnedItem.h"
#include "../Model/Member.h"
#include "../Model/Error.h"
#include "../Controller/SELController.h"

#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMessageBox>
#include <QtCore/QStringList>

const int SELUserAccountWidget::ROWS_PER_PAGE = 10;
const int SELUserAccountWidget::NUM_COLUMNS = 4;

///
const int WIDTH_OFFSET = 30;

SELUserAccountWidget::SELUserAccountWidget(SELController & controller, QWidget * parent) :
    QWidget(parent), controller(controller), requestIds(0), userLoansChanged(false)
{
    QStringList headers;
    const char * headerContents[] = {"Date", "Member", "Item", "Status"};
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
    for (int i = 0; i < ROWS_PER_PAGE; i++) {
        for (int j = 0; j < NUM_COLUMNS; j++) {
            messageTableWidget->setItem(i, j, new QTableWidgetItem());
        }
    }
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

bool SELUserAccountWidget::checkUserLoansChanged()
{
    return userLoansChanged;
}

void SELUserAccountWidget::setUserLoansChanged(bool changed)
{
    userLoansChanged = changed;
}

void SELUserAccountWidget::updateMessagesTable(LoanRequest * requests, unsigned numRequests)
{
    unsigned i;
    
    for (i = 0; i < numRequests; i++) {
        messageTableWidget->item(i, 0)->setText(requests[i].getStartDate().toString("dd/MM/yyyy"));
        messageTableWidget->item(i, 1)->setText(requests[i].getRequestingMember().getUsername().c_str());
        messageTableWidget->item(i, 2)->setText(requests[i].getRequestedItem().getTitle().c_str());
        messageTableWidget->item(i, 3)->setText(LoanRequest::getRequestStatusString(requests[i].getRequestStatus()).c_str());
        requestIds[i] = requests[i].getRequestId();
    }

    while (i < (unsigned)ROWS_PER_PAGE) {
        messageTableWidget->item(i, 0)->setText("");
        messageTableWidget->item(i, 1)->setText("");
        messageTableWidget->item(i, 2)->setText("");
        messageTableWidget->item(i, 3)->setText("");
        requestIds[i] = 0;
        i++;
    }

    if (requests != 0) {
        delete [] requests;
    }
}

void SELUserAccountWidget::loadUserData()
{
    Member * member = 0;
    
    member = controller.retrieveData();
    if (member != 0) {
        usernameLineEdit->setText(member->getUsername().c_str());
        emailLineEdit->setText(member->getEmail().c_str());
        delete member;
    }
}

void SELUserAccountWidget::loadFirstMessagePage()
{
    LoanRequest * requests = 0;
    int numRequests = 0;
    
    requests = controller.retrieveMessagePage(1, numRequests);
    if (requests != 0) {
        updateMessagesTable(requests, numRequests);
    }
}

void SELUserAccountWidget::reloadMessagePage()
{
    LoanRequest * requests = 0;
    int numRequests = 0;
    int curPage = currentPageLabel->text().toInt();
    
    requests = controller.retrieveMessagePage(curPage, numRequests);
    if (requests != 0) {
        updateMessagesTable(requests, (unsigned)numRequests);
    } else if (numRequests > 0) {
        Error::raiseError(Error::ERROR_PAGE_RELOAD_FAIL);
    } else {
        updateMessagesTable(0, 0);
    }
}

/////////////
// Private //
/////////////

void SELUserAccountWidget::updatePageIndexNext()
{
    LoanRequest * requests = 0;
    int numRequests = 0;
    int pageToGet;
    bool ok;
    
    pageToGet = currentPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet++;
        requests = controller.retrieveMessagePage(pageToGet, numRequests);
        if ((requests != 0) && (numRequests > 0)) {
            currentPageLabel->setNum(pageToGet);
            updateMessagesTable(requests, (unsigned)numRequests);
        }
    }
}

void SELUserAccountWidget::updatePageIndexPrevious()
{
    LoanRequest * requests = 0;
    int numRequests = 0;
    int pageToGet;
    bool ok;
    
    pageToGet = currentPageLabel->text().toInt(&ok);
    
    if (ok) {
        pageToGet--;
        if (pageToGet > 0) {
            requests = controller.retrieveMessagePage(pageToGet, numRequests);
            if ((requests != 0) && (numRequests > 0)) {
                currentPageLabel->setNum(pageToGet);
                updateMessagesTable(requests, (unsigned)numRequests);
            }
        }
    }
}

void SELUserAccountWidget::emitIdShowData(QTableWidgetItem * item)
{
    QMessageBox dialog(QMessageBox::NoIcon, "Loan Request", "");
    unsigned long long id = findId(item);
    unsigned answer;
    string * message = 0;
    
    if (id > 0) {
        message = controller.getMessage(id);
        if (message != 0) {
            dialog.setText(message->c_str());
            dialog.setInformativeText("Would you like to loan the item?");
            dialog.setStandardButtons(QMessageBox::Ok | QMessageBox::No | QMessageBox::Cancel);
            dialog.setDefaultButton(QMessageBox::No);
            answer = dialog.exec();
            sendMessageReply(answer, id);
            delete message;
        }
    } else {
        Error::raiseError(Error::ERROR_REQ_ID_NOT_FOUND);
    }
}

/////////////
// Private //
/////////////

unsigned long long SELUserAccountWidget::findId(QTableWidgetItem * item)
{
    int i, j, row;
    bool found = false;
    unsigned long long foundId;
    
    for (i = 0; i < ROWS_PER_PAGE && !found; i++) {
        for (j = 0; j < NUM_COLUMNS && !found; j++) {
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

void SELUserAccountWidget::sendMessageReply(unsigned reply, unsigned long long requestId)
{
    QMessageBox dialog(QMessageBox::NoIcon, "Loan Request", "Action impossible. Rejecting loan.");
    LoanRequest * request = controller.retrieveRequest(requestId);
    bool opSuccess = false;
    
    switch (reply) {
    case QMessageBox::Ok:
        /// If loan is possible:
        if (!controller.checkIfLoanPossible(request)) {
            opSuccess = controller.processRequestReply(requestId, true);
            userLoansChanged = true;
        } else {
            dialog.exec();
            opSuccess = controller.processRequestReply(requestId, false);
        }
        break;
    case QMessageBox::No:
        opSuccess = controller.processRequestReply(requestId, false);
        break;
    default:
        break;
    }
    if (request != 0) {
        delete request;
    }
    
    if (opSuccess) {
        reloadMessagePage();
    }   
}

