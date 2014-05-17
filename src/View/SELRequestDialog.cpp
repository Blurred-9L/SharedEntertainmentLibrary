#include "SELRequestDialog.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>

SELRequestDialog::SELRequestDialog(QWidget * parent) :
    QDialog(parent), memberIds(0)
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QVBoxLayout * memberListLayout = new QVBoxLayout();
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(memberListLayout);
    mainLayout->addLayout(buttonLayout);
    
    membersLabel = new QLabel("Available members:");
    memberListLayout->addWidget(membersLabel);
    
    membersListWidget = new QListWidget();
    memberListLayout->addWidget(membersListWidget);
    
    selectMemberButton = new QPushButton("Request loan");
    buttonLayout->addWidget(selectMemberButton);
    
    cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
}

SELRequestDialog::~SELRequestDialog()
{
    if (memberIds != 0) {
        delete [] memberIds;
    }
}
