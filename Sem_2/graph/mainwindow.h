#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget4graph.h"
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
    void addVertex();
    void deleteVertex();
    void addEdge();
    void deleteEdge();
    void answerBy();
    void answerTSP();
    void clearGraph();
    void initGraph11();
    void initGraphTSP();

  private:
    QWidget *central;
    GLWidget4Graph *openGlW;
    Graph *graph;
};
#endif // MAINWINDOW_H
