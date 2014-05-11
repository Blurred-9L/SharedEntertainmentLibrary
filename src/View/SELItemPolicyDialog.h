#ifndef SEL_ITEM_POLICY_DIALOG_H
#define SEL_ITEM_POLICY_DIALOG_H

#include <QtGui/QDialog>

class QLabel;
class QComboBox;
class QPushButton;

class EntertainmentItem;

class SELItemPolicyDialog : public QDialog {
Q_OBJECT

private:
    ///
    EntertainmentItem * item;
    ///
    unsigned long long ownedItemId;
    ///
    unsigned long long policy;
    ///
    QLabel * promptLabel;
    ///
    QLabel * titleLabel;
    ///
    QLabel * currentPolicyLabel;
    ///
    QComboBox * policiesComboBox;
    ///
    QPushButton * acceptButton;
    ///
    QPushButton * cancelButton;
    ///
    int curIndex;

public:
    ///
    SELItemPolicyDialog(EntertainmentItem * item,
                        unsigned long long ownedItemId,
                        unsigned long long policy,
                        QWidget * parent = 0);
    ///
    virtual ~SELItemPolicyDialog();
    
public slots:
    ///
    void setIndex(int newIndex);
    ///
    void cancelOperation();
    ///
    void acceptOperation();
};

#endif /// NOT_SEL_ITEM_POLICY_DIALOG_H
