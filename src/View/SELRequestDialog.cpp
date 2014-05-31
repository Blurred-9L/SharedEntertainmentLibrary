#include "SELRequestDialog.h"
#include "../Model/Member.h"
#include "../Model/OwnedItem.h"
#include "../Model/Error.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtCore/QList>

SELRequestDialog::SELRequestDialog(unsigned long long itemId, OwnedItem * items,
                                   int numItems, QWidget * parent) :
    QDialog(parent), itemId(itemId), ownedItems(items), numItems(numItems)
{
    QString itemString;
    
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QVBoxLayout * memberListLayout = new QVBoxLayout();
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(memberListLayout);
    mainLayout->addLayout(buttonLayout);
    
    membersLabel = new QLabel("Available members:");
    memberListLayout->addWidget(membersLabel);
    
    membersListWidget = new QListWidget();
    for (int i = 0; i < numItems; i++) {
        itemString += items[i].getOwner().getUsername().c_str();
        membersListWidget->addItem(new QListWidgetItem(itemString));
    }
    memberListLayout->addWidget(membersListWidget);
    
    selectMemberButton = new QPushButton("Request loan");
    buttonLayout->addWidget(selectMemberButton);
    
    cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    
    /// Cancel button pressed -> request is cancelled.
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelRequest()));
    /// Accept button pressed -> tries to accept request.
    connect(selectMemberButton, SIGNAL(clicked()), this, SLOT(acceptRequest()));
}

SELRequestDialog::~SELRequestDialog()
{
}

void SELRequestDialog::cancelRequest()
{
    this->done(-1);
}

void SELRequestDialog::acceptRequest()
{
    QList<QListWidgetItem *> items = membersListWidget->selectedItems();
    int size = items.size();
    int index;
    
    if (size == 1) {
        index = find(items[0]);
        this->done(index);
    } else if (size > 1) {
        Error::raiseError(Error::ERROR_ITEM_SELECTION_ERROR);
    } else {
        Error::raiseError(Error::ERROR_NO_ITEM_SELECTED);
    }
}

/////////////
// Private //
/////////////

int SELRequestDialog::find(QListWidgetItem * item)
{
    QList<QListWidgetItem *> items = membersListWidget->findItems("*", Qt::MatchWildcard);
    QList<QListWidgetItem *>::iterator i;
    bool found = false;
    int index = 0;
    
    for (i = items.begin(); i != items.end() && !found; i++) {
        if ((*i) == item) {
            found = true;
        } else {
            index++;
        }
    }
    
    if (index == items.size()) {
        index = -1;
    }
    
    return index;
}
