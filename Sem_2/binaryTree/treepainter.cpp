#include "treepainter.h"
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

TreePainter::TreePainter()
{
    glFont.setPixelSize(14);
    circleRadius = 18;
}

void TreePainter::draw(QPainter *painter, QPaintEvent *event, Node *rootNode)
{
    painter->fillRect(event->rect(), Qt::lightGray);
    painter->setPen(Qt::black);
    painter->setFont(glFont);
    if (rootNode != nullptr)
    {
        int startX = event->rect().width() / 2;
        int startY = 40;
        int horizontalSpacing = 280;
        int verticalSpacing = 70;
        drawNode(painter, rootNode, startX, startY, horizontalSpacing, verticalSpacing);
    }
}

void TreePainter::drawNode(QPainter *painter, Node *node, int x, int y, int hSpacing, int vSpacing)
{
    int childX, childY;
    if (node->left != nullptr)
    {
        childX = x - hSpacing;
        childY = y + vSpacing;
        painter->drawLine(x, y, childX, childY);
        drawNode(painter, node->left, childX, childY, hSpacing / 2, vSpacing);
    }
    if (node->right != nullptr)
    {
        childX = x + hSpacing;
        childY = y + vSpacing;
        painter->drawLine(x, y, childX, childY);
        drawNode(painter, node->right, childX, childY, hSpacing / 2, vSpacing);
    }
    QRect circle(x - circleRadius, y - circleRadius, 2 * circleRadius, 2 * circleRadius);
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(circle);
    painter->drawText(circle, Qt::AlignCenter, QString::number(node->data));
}
