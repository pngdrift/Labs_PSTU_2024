#ifndef TREEPAINTER_H
#define TREEPAINTER_H

#include "tree.h"
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class TreePainter
{
  public:
    TreePainter();

  public:
    void draw(QPainter *painter, QPaintEvent *event, Node *rootNode);
    void drawNode(QPainter *painter, Node *node, int x, int y, int hSpacing, int vSpacing);

  private:
    QFont glFont;
    int circleRadius;
};

#endif // TREEPAINTER_H
