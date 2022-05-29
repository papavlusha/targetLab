#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QSize>
#include <QPushButton>
#include <QLabel>
#include <target.h>
#include <QLineEdit>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void boom();
    bool eventFilter(QObject* watched, QEvent* event);
    void startGame();
private:
    QVBoxLayout *mainVerticalLayout_;
    QHBoxLayout *topHorizontalLayout_;
    QHBoxLayout *bottomInfoLayout_;
    QLabel *inputInfo_;
    QLabel *topInfo_;
    QLabel *ShootsAmount_;
    QLineEdit *shootsSetter_;
    QLabel *shootsNumber_;
    QLabel *hitsNumber_;
    QLabel *missNumber_;
    QLineEdit *setX_;
    QLineEdit *setY_;
    QPushButton *action_;
    QWidget *target_;
    target *t;
    QPushButton *setButton;
    int amount = -1;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
