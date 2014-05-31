#ifndef SEL_REQUEST_DIALOG_H
#define SEL_REQUEST_DIALOG_H

#include <QtGui/QDialog>

class QListWidget;
class QListWidgetItem;
class QPushButton;
class QLabel;

class OwnedItem;

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
    unsigned long long itemId;
    ///
    OwnedItem * ownedItems;
    ///
    int numItems;
    
    ///
    int find(QListWidgetItem * item);

public:
    ///
    SELRequestDialog(unsigned long long itemId, OwnedItem * items,
                     int numItems, QWidget * parent = 0);
    ///
    virtual ~SELRequestDialog();
    
public slots:
    ///
    void cancelRequest();
    ///
    void acceptRequest();
};

#endif /// Not SEL_REQUEST_DIALOG_H
