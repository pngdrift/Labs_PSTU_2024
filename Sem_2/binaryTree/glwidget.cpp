#include "glwidget.h"
#include <QPainter>
#include <QRandomGenerator>

GLWidget::GLWidget(TreePainter *tp, QWidget *parent) : QOpenGLWidget(parent), treePainter(tp)
{
    rootNode = nullptr;
}

void GLWidget::redraw(Node *rootNode)
{
    this->rootNode = rootNode;
    update();
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    treePainter->draw(&painter, event, rootNode);
    painter.end();
}
