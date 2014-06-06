#include "SELMessageReqDialog.h"
#include "../Model/Error.h"

#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtGui/QDateEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>

SELMessageReqDialog::SELMessageReqDialog(QString & message, QDate & loanDate,
                                         int & nLoanDays, QWidget * parent) :
    QDialog(parent), message(message), loanDate(loanDate), nLoanDays(nLoanDays)
{
    QDate minDate(QDate::currentDate());
    
    minDate.addDays(1);
    
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * loanLayout = new QHBoxLayout();
    QVBoxLayout * dateLayout = new QVBoxLayout();
    QVBoxLayout * durationLayout = new QVBoxLayout();
    QVBoxLayout * messageLayout = new QVBoxLayout();
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(loanLayout);
    mainLayout->addLayout(messageLayout);
    mainLayout->addLayout(buttonLayout);
    
    loanLayout->addLayout(dateLayout);
    loanLayout->addLayout(durationLayout);
    
    dateLabel = new QLabel("Start date:");
    dateLayout->addWidget(dateLabel);
    
    datePicker = new QDateEdit();
    datePicker->setMinimumDate(minDate);
    datePicker->setDate(minDate);
    dateLayout->addWidget(datePicker);
    
    durationLabel = new QLabel("Duration:");
    durationLayout->addWidget(durationLabel);
    
    loanDaysSpinBox = new QSpinBox();
    loanDaysSpinBox->setMinimum(3);
    loanDaysSpinBox->setMaximum(28);
    loanDaysSpinBox->setSuffix(" days");
    loanDaysSpinBox->setValue(3);
    durationLayout->addWidget(loanDaysSpinBox);
    
    messageLabel = new QLabel("Short message:");
    messageLayout->addWidget(messageLabel);
    
    messageTextEdit = new QTextEdit();
    messageTextEdit->setAcceptRichText(false);
    messageLayout->addWidget(messageTextEdit);
    
    acceptButton = new QPushButton("Accept");
    buttonLayout->addWidget(acceptButton);
    
    cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(onAccept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));
}

SELMessageReqDialog::~SELMessageReqDialog()
{
}

void SELMessageReqDialog::onAccept()
{
    int messageLength = messageTextEdit->toPlainText().length();
    
    if (messageLength < 1023) {
        message = messageTextEdit->toPlainText();
        loanDate = datePicker->date();
        nLoanDays = loanDaysSpinBox->value();
        done(0);
    } else {
        Error::raiseError(Error::ERROR_MESSAGE_TOO_LONG);
    }
}

void SELMessageReqDialog::onCancel()
{
    done(-1);
}
