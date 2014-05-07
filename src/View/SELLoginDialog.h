#ifndef SEL_LOGIN_DIALOG_H
#define SEL_LOGIN_DIALOG_H

#include <QtGui/QDialog>

class QLineEdit;
class QLabel;
class QPushButton;
class SELController;

/**
 *  @class  SELLoginDialog
 */
class SELLoginDialog : public QDialog {
Q_OBJECT

private:
    ///
    SELController & controller;
    ///
    QLabel * usernameLabel;
    ///
    QLabel * passwordLabel;
    ///
    QLineEdit * usernameLineEdit;
    ///
    QLineEdit * passwordLineEdit;
    ///
    QPushButton * acceptButton;
    ///
    QPushButton * cancelButton;

public:
    ///
    SELLoginDialog(SELController & controller, QWidget * parent = 0);
    ///
    virtual ~SELLoginDialog();
    
private slots:
    ///
    void validateInput();
    
signals:
    ///
    void loginSuccessful();
};

#endif /// Not SEL_LOGIN_DIALOG_H
