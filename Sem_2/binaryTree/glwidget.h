#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "treepainter.h"
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
  public:
    GLWidget(TreePainter *tp, QWidget *parent);

  public slots:
    void redraw(Node *);

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    TreePainter *treePainter;
    Node *rootNode;
};
#endif // MYGLWIDGET_H
