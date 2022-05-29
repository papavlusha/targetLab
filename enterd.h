
#ifndef ENTERD_H
#define ENTERD_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class EnterDialog : public QDialog
{

    Q_OBJECT

public:

    EnterDialog(QWidget *parent = 0);
    int Radius_;
    int getR() const;
private slots:

    void AcceptClicked();
    void enableFindButton(const QString &text);

private:
    QLabel *infoLabel_;
    QLineEdit *inputLineEdit_;
    QPushButton *addButton_;
    QPushButton *closeButton_;

};

#endif // ENTERD_H
