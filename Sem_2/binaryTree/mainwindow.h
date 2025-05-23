#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initMenuBar();

  public slots:
    void reinitTree();
    void addNode();
    // void removeNode();
    void balanceTree();

  private:
    QWidget *central;
    Tree *binTree;
    GLWidget *openGlW;
    QLabel *minElemLabel;

    void printMinElem();
};
#endif // MAINWINDOW_H
