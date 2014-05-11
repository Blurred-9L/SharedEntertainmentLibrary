#include "SELItemPolicyDialog.h"
#include "../Model/EntertainmentItem.h"
#include "../Model/OwnedItem.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QPushButton>

SELItemPolicyDialog::SELItemPolicyDialog(EntertainmentItem * item,
                                         unsigned long long ownedItemId,
                                         unsigned long long policy,
                                         QWidget * parent) :
    QDialog(parent), item(item), ownedItemId(ownedItemId),
    policy(policy), curIndex(0)
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    
    promptLabel = new QLabel("Select the new loan policy for:");
    promptLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(promptLabel);
    
    titleLabel = new QLabel(item->getTitle().c_str());
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    currentPolicyLabel = new QLabel();
    switch (policy) {
    case OwnedItem::POLICY_FREE:
        currentPolicyLabel->setText("Current policy: Free policy");
        break;
    case OwnedItem::POLICY_USER:
        currentPolicyLabel->setText("Current policy: User policy");
        break;
    case OwnedItem::POLICY_NO_LOAN:
        currentPolicyLabel->setText("Current policy: No loans policy");
        break;
    default:
        currentPolicyLabel->setText("Current policy: Invalid");
        break;
    }
    currentPolicyLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(currentPolicyLabel);
    
    policiesComboBox = new QComboBox();
    policiesComboBox->addItem("Free policy", OwnedItem::POLICY_FREE);
    policiesComboBox->addItem("User policy", OwnedItem::POLICY_USER);
    policiesComboBox->addItem("No loans", OwnedItem::POLICY_NO_LOAN);
    policiesComboBox->setEditable(false);
    mainLayout->addWidget(policiesComboBox);
    
    mainLayout->addLayout(buttonLayout);
    
    acceptButton = new QPushButton("Accept");
    buttonLayout->addWidget(acceptButton);
    
    cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    
    /// Connects signals.
    ///
    connect(policiesComboBox, SIGNAL(activated(int)),
            this, SLOT(setIndex(int)));
    ///
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelOperation()));
    ///
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(acceptOperation()));
}

SELItemPolicyDialog::~SELItemPolicyDialog()
{
}

void SELItemPolicyDialog::setIndex(int newIndex)
{
    curIndex = newIndex;
}

void SELItemPolicyDialog::cancelOperation()
{
    this->done(0);
}

void SELItemPolicyDialog::acceptOperation()
{
    if (curIndex >= 0) {
        this->done(policiesComboBox->itemData(curIndex).toInt());
    } else {
        this->done(0);
    }
}
