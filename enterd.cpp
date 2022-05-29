#include "enterd.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

EnterDialog::EnterDialog(QWidget *parent)
      : QDialog(parent)
  {

    infoLabel_ = new QLabel(tr("Input &Rad(100-250):"));
    inputLineEdit_ = new QLineEdit;
    inputLineEdit_->setInputMask("999");
    infoLabel_->setBuddy(inputLineEdit_);
    addButton_ = new QPushButton(tr("&OK"));
    addButton_->setDefault(true);
    addButton_->setEnabled(false);
    closeButton_ = new QPushButton(tr("Cancel"));
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(infoLabel_);
    topLeftLayout->addWidget(inputLineEdit_);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);

    QHBoxLayout *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(closeButton_);
    rightLayout->addWidget(addButton_);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Input"));
    setFixedHeight(sizeHint().height());

    connect(inputLineEdit_, SIGNAL(textChanged(const QString &)),
        this, SLOT(enableFindButton(const QString &)));
    connect(addButton_, SIGNAL(clicked()),
        this, SLOT(AcceptClicked()));
    connect(closeButton_, SIGNAL(clicked()),
        this, SLOT(close()));
}

int EnterDialog::getR() const {
    return Radius_;
}

void EnterDialog::AcceptClicked() {
    Radius_ = inputLineEdit_->text().toInt();
    if (Radius_ < 100) {
        Radius_ = 100;
    }
    if(Radius_ >= 250) {
        Radius_ = 250;
    }
    close();
 }

void EnterDialog::enableFindButton(const QString &text) {
    addButton_->setEnabled(!text.isEmpty());
}
