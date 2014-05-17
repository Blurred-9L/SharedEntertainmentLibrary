#ifndef SEL_REQUEST_DIALOG_H
#define SEL_REQUEST_DIALOG_H

#include <QtGui/QDialog>

class QListWidget;
class QPushButton;
class QLabel;

class SELRequestDialog : public QDialog {
Q_OBJECT

private:
    ///
    QListWidget * membersListWidget;
    ///
    QPushButton * selectMemberButton;
    ///
    QPushButton * cancelButton;
    ///
    QLabel * membersLabel;
    ///
    unsigned long long * memberIds;

public:
    ///
    SELRequestDialog(QWidget * parent = 0);
    ///
    virtual ~SELRequestDialog();
};

#endif /// Not SEL_REQUEST_DIALOG_H
