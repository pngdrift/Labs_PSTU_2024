#ifndef GLWIDGET4GRAPH_H
#define GLWIDGET4GRAPH_H

#include "graph.h"
#include "qevent.h"
#include <QBrush>
#include <QFont>
#include <QOpenGLWidget>

class GLWidget4Graph : public QOpenGLWidget
{
    Q_OBJECT
  public:
    GLWidget4Graph(QWidget *parent, Graph *g);
    void draw(QPainter *painter, QPaintEvent *event, Graph *graph);

  public slots:
    void redraw();

  protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

  private:
    Graph *graph;
    QFont glFont;
    int draggingVertex;
};
#endif // GLWIDGET4GRAPH_H
