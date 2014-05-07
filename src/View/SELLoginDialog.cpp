#include "SELLoginDialog.h"
#include "../Model/Error.h"
#include "../Model/LoginModel.h"

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QRegExpValidator>

const int MAX_USERNAME_LENGTH = 24;
const int MAX_PASSWORD_LENGTH = 18;
const int MIN_USERNAME_LENGTH = 6;
const int MIN_PASSWORD_LENGTH = 8;

SELLoginDialog::SELLoginDialog(QWidget * parent) :
    QDialog(parent)
{
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * usernameLayout = new QHBoxLayout();
    QHBoxLayout * passwordLayout = new QHBoxLayout();
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    
    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(buttonLayout);
    
    usernameLabel = new QLabel("Username:");
    usernameLayout->addWidget(usernameLabel);
    
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setMaxLength(MAX_USERNAME_LENGTH);
    usernameLayout->addWidget(usernameLineEdit);
    
    passwordLabel = new QLabel("Password:");
    passwordLayout->addWidget(passwordLabel);
    
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setMaxLength(MAX_PASSWORD_LENGTH);
    passwordLayout->addWidget(passwordLineEdit);
    
    acceptButton = new QPushButton("Log in");
    buttonLayout->addWidget(acceptButton);
    
    cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    
    resize(275, 200);
    
    /// When accept button is pressed, validate input
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(validateInput()));
    /// When input has been validated, try login
    /// If login successful, return true.
    connect(this, SIGNAL(loginSuccessful(long long int)),
            this, SLOT(accept()));
    /// If login not successful, show wrong login dialog.
    /// If input is wrong, show wrong input dialog.
    /// When cancel button is pressed, end application.
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

SELLoginDialog::~SELLoginDialog()
{
}

void SELLoginDialog::validateInput()
{
    QRegExp usernameRegex("[a-zA-Z_$&!][a-zA-Z_0-9$&!]{5,23}");
    QRegExp passwordRegex("[a-zA-Z_\\-0-9!#$%&*+,.]{8,18}");
    QRegExpValidator usernameValidator(usernameRegex);
    QRegExpValidator passwordValidator(passwordRegex);
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    LoginModel loginModel;
    bool validInput = true;
    bool correctUsername = false;
    bool correctPassword = false;
    unsigned long long userId;
    int pos = 0;
    
    correctUsername = (usernameValidator.validate(username, pos) == QValidator::Acceptable);
    correctPassword = (passwordValidator.validate(password, pos) == QValidator::Acceptable);
    validInput = (correctUsername && correctPassword);
    
    if (validInput) {
        userId = loginModel.tryLogin(username.toAscii().data(), password.toAscii().data());
        if (userId != 0) {
            emit loginSuccessful(userId);
        } else {
            Error::raiseError(Error::ERROR_LOGIN_FAIL);
        }
    } else if (!correctUsername) {
        if (username.length() > MAX_USERNAME_LENGTH) {
            Error::raiseError(Error::ERROR_USERNAME_LONG);
        } else if (username.length() < MIN_USERNAME_LENGTH) {
            Error::raiseError(Error::ERROR_USERNAME_SHORT);
        } else {
            Error::raiseError(Error::ERROR_USERNAME_FORMAT);
        }
    } else if (!correctPassword) {
        if (password.length() > MAX_PASSWORD_LENGTH) {
            Error::raiseError(Error::ERROR_PASSWORD_LONG);
        } else if (password.length() < MIN_PASSWORD_LENGTH) {
            Error::raiseError(Error::ERROR_PASSWORD_SHORT);
        } else {
            Error::raiseError(Error::ERROR_PASSWORD_FORMAT);
        }
    }
}

