#include "mainwindow.h"
#include <QDebug>
#include "enterd.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    EnterDialog enter;
    enter.exec();
    t = new target(enter.getR());
    t->generatePas();
    this->installEventFilter(this);
    auto w = new QWidget;
    topHorizontalLayout_ = new QHBoxLayout;
    mainVerticalLayout_ = new QVBoxLayout;
    action_ = new QPushButton;
    setButton = new QPushButton;
    target_ = new QWidget;
    setX_ = new QLineEdit;
    setY_ = new QLineEdit;
    shootsSetter_ = new QLineEdit;
    shootsSetter_->setInputMask("999999");
    bottomInfoLayout_ = new QHBoxLayout;
    topInfo_ = new QLabel;
    ShootsAmount_ = new QLabel;
    shootsNumber_ = new QLabel;
    hitsNumber_ = new QLabel;
    missNumber_ = new QLabel;
    setX_->setInputMask("#999");
    setY_->setInputMask("#999");
    inputInfo_ = new QLabel;
    topInfo_ = new QLabel;
    inputInfo_->setText("Введите координаты X , Y");
    action_->setText("Шмаляем по координатам");
    setButton ->setText("Установить");
    topHorizontalLayout_->addWidget(inputInfo_);
    topHorizontalLayout_->addWidget(setX_);
    topHorizontalLayout_->addWidget(setY_);
    mainVerticalLayout_->addLayout(topHorizontalLayout_);
    mainVerticalLayout_->addWidget(action_);
    target_->setMinimumSize(700,700);
    topInfo_->setText("Перед началом установите количество выстрелов снизу");
    mainVerticalLayout_->addWidget(topInfo_);
    mainVerticalLayout_->addWidget(target_);
    ShootsAmount_->setText("Количество выстрелов");
    shootsNumber_->setText("Выстрелов");
    hitsNumber_->setText("Попаданий");
    missNumber_->setText("Промахов");
    bottomInfoLayout_->addWidget(ShootsAmount_);
    bottomInfoLayout_->addWidget(shootsSetter_);
    bottomInfoLayout_ -> addWidget(setButton);
    bottomInfoLayout_->addWidget(shootsNumber_);
    bottomInfoLayout_->addWidget(hitsNumber_);
    bottomInfoLayout_->addWidget(missNumber_);
    mainVerticalLayout_->addLayout(bottomInfoLayout_);
    setCentralWidget(w);
    w->setLayout(mainVerticalLayout_);
    target_->installEventFilter(this);
    w->installEventFilter(this);
    setFixedSize(700,700);
    connect(action_,SIGNAL(clicked()),SLOT(boom()));
    action_->setEnabled(false);
    connect(setButton,SIGNAL(clicked()),SLOT(startGame()));
}
MainWindow::~MainWindow()
{
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == target_ && event->type() == QEvent::Paint) {
        QPainter painter;
        painter.begin(target_);
        int l = target_->y();
        int R = t->getR();
        painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
        painter.drawEllipse(target_->width()/2-R,target_->height()/2-R-l, R*2,R*2);//+
        QLine lineX(target_->width()/2-R,target_->height()/2-l,target_->width()/2+R,target_->height()/2-l);//
        QLine lineY(target_->width()/2,target_->height()/2-R-l,target_->width()/2,target_->height()/2+R-l);//
        painter.drawLine(lineX);
        painter.drawLine(lineY);
        painter.drawPoint(target_->width()/2,target_->height()/2-l);
        QPainterPath path;
        QBrush brush;
        brush.setColor(Qt::gray);
        painter.setBrush(QBrush(Qt::gray));
        path.moveTo(t->points_[0].first+target_->width()/2,-t->points_[0].second+target_->height()/2-l);
        for (int i =1; i < (int)t->points_.size();i++) {
                   path.lineTo(t->points_[i].first+target_->width()/2,-t->points_[i].second+target_->height()/2-l);
               }
        painter.drawPath(path);
        painter.drawPie(target_->width()/2-R,target_->height()/2-R-l, R*2,R*2,180*16,90*16);
        painter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::FlatCap));
        for (int  i =0; i < (int)t->hitsCoor_.size(); i++) {
            painter.drawPoint(t->hitsCoor_[i].first + target_->width()/2 ,-t->hitsCoor_[i].second + target_->height()/2-l);
        }
        painter.end();
        return true;
    }
    return false;
}

void MainWindow::boom() {
     if(amount == -1) {
         return;
     }
     int x = setX_->text().toInt();
     int y = setY_->text().toInt();
     if(t->shoot(x,y)) {
       update();
       ShootsAmount_->setText("последний выстрел попал"
                            "");
    } else {
         ShootsAmount_->setText("последний выстрел ушел мимо");
     }
     shootsNumber_->setText("Выстрелов:" +  QString::number(t->getShoots()));
     hitsNumber_->setText("Попаданий:" + QString::number(t->getHits()));
     missNumber_->setText("Промахов:" + QString::number(t->getShoots()-t->getHits()));
     amount--;
     if (amount == 0) {
         if(QMessageBox::question(this,"Игра закончена!","Хотите еще сыграть?",
                               QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
              QApplication::quit();
        else {
          amount = -1;
          t->ClearAmount();
          t->hitsCoor_.clear();
          action_->setEnabled(false);
          shootsSetter_->setEnabled(true);
          setButton->setEnabled(true);
          shootsSetter_->setText("");
          shootsNumber_->setText("0");
          hitsNumber_->setText("0");
          missNumber_->setText("0");
          ShootsAmount_->setText("Количество");
          topInfo_->setText("Перед началом установите количество выстрелов снизу");
        }
     }
  }
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        int  aX = event->x()-target_->width()/2-10;
        int  aY = -(event->y()-target_->height()/2);
        setX_->setText(QString::number(aX));
        setY_->setText(QString::number(aY));
        boom();
    }
}

void MainWindow::startGame() {
    if (shootsSetter_->text().toInt() == 0) {
        return;
    }
    amount = shootsSetter_->text().toInt();
    action_->setEnabled(true);
    shootsSetter_->setEnabled(false);
    setButton->setEnabled(false);
    topInfo_->setText("давайте стрелять (0,0) центр мишени");

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space) {
        action_->click();
    }
}
