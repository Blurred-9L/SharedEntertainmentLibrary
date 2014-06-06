#ifndef SEL_MESSAGE_REQ_DIALOG_H
#define SEL_MESSAGE_REQ_DIALOG_H

#include <QtGui/QDialog>

class QDate;
class QString;
class QDateEdit;
class QTextEdit;
class QSpinBox;
class QPushButton;
class QLabel;

class SELMessageReqDialog : public QDialog {
Q_OBJECT

private:
    ///
    QString & message;
    ///
    QDate & loanDate;
    ///
    int & nLoanDays;
    ///
    QDateEdit * datePicker;
    ///
    QTextEdit * messageTextEdit;
    ///
    QSpinBox * loanDaysSpinBox;
    ///
    QPushButton * acceptButton;
    ///
    QPushButton * cancelButton;
    ///
    QLabel * dateLabel;
    ///
    QLabel * messageLabel;
    ///
    QLabel * durationLabel;

public:
    ///
    SELMessageReqDialog(QString & message, QDate & loanDate,
                        int & nLoanDays, QWidget * parent = 0);
    ///
    virtual ~SELMessageReqDialog();
    
public slots:
    ///
    void onAccept();
    ///
    void onCancel();
};

#endif /// Not SEL_MESSAGE_REQ_DIALOG_H
