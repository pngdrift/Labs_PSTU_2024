#include "glwidget4graph.h"
#include "qevent.h"
#include <QPainter>
#include <QRandomGenerator>

GLWidget4Graph::GLWidget4Graph(QWidget *parent, Graph *g) : QOpenGLWidget(parent), graph(g)
{
    draggingVertex = -1;
    glFont.setPixelSize(18);
}

void GLWidget4Graph::redraw()
{
    update();
}

void GLWidget4Graph::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    this->draw(&painter, event, graph);
    painter.end();
}

void GLWidget4Graph::draw(QPainter *painter, QPaintEvent *event, Graph *graph)
{
    painter->fillRect(event->rect(), Qt::gray);
    painter->setPen(Qt::black);
    painter->setFont(glFont);
    int circleRadius = 28;
    int vertLen = graph->vertices.size();
    for (int i = 0; i < vertLen; ++i)
    {
        for (int j = 0; j < vertLen; ++j)
        {
            int weight = graph->adjMatrix[i][j];
            if (weight > 0)
            {
                const Vertex &v1 = graph->vertices[i];
                const Vertex &v2 = graph->vertices[j];
                QPoint p1(v1.x, v1.y);
                QPoint p2(v2.x, v2.y);
                QLine line(p1, p2);
                painter->setPen(Qt::black);
                painter->drawLine(line);
                int midX = (p1.x() + p2.x()) / 2;
                int midY = (p1.y() + p2.y()) / 2;
                painter->setPen(Qt::white);
                painter->drawText(midX, midY, QString::number(weight));
            }
        }
    }
    painter->setPen(Qt::black);
    painter->setBrush(Qt::darkRed);
    for (int i = vertLen - 1; i >= 0; --i)
    {
        const Vertex &v = graph->vertices[i];
        QRect circle(v.x - circleRadius, v.y - circleRadius, 2 * circleRadius, 2 * circleRadius);
        painter->drawEllipse(circle);
        painter->drawText(circle, Qt::AlignCenter, QString::number(v.id));
    }
}

void GLWidget4Graph::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    auto vertices = graph->vertices;
    int vertLen = vertices.size();
    for (int i = 0; i < vertLen; ++i)
    {
        float dx = x - vertices[i].x;
        float dy = y - vertices[i].y;
        if (std::sqrt(dx * dx + dy * dy) < 30)
        {
            if (event->button() == Qt::MouseButton::RightButton)
            {
                draggingVertex = -1;
                graph->eraseVertex(vertices[i]);
            }
            else
            {
                draggingVertex = i;
            }
            break;
        }
    }
    redraw();
}

void GLWidget4Graph::mouseReleaseEvent(QMouseEvent *event)
{
    draggingVertex = -1;
}

void GLWidget4Graph::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x(), y = event->pos().y();
    if (draggingVertex != -1)
    {
        graph->vertices[draggingVertex].x = x;
        graph->vertices[draggingVertex].y = y;
        update();
    }
}
