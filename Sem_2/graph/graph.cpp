#include "graph.h"
#include "qdebug.h"
#include <QRandomGenerator>
#include <QString>
#include <iostream>
#include <limits>

Vertex::Vertex()
{
    x = QRandomGenerator::global()->bounded(25, 900);
    y = QRandomGenerator::global()->bounded(25, 600);
    static char newId = 0;
    id = ++newId;
}

Graph::Graph()
{
    for (int i = 0; i < maxSize; ++i)
    {
        for (int j = 0; j < maxSize; ++j)
        {
            adjMatrix[i][j] = 0;
        }
    }
}

int Graph::getVertexPos(const Vertex &vertex)
{
    int vertexLen = vertices.size();
    for (int i = 0; i < vertexLen; ++i)
    {
        if (vertices[i] == vertex)
        {
            return i;
        }
    }
    return -1;
}

const Vertex *Graph::getVertexById(unsigned char id)
{
    int vertexLen = vertices.size();
    for (int i = 0; i < vertexLen; ++i)
    {
        if (vertices[i].id == id)
        {
            return &vertices[i];
        }
    }
    return nullptr;
}

int Graph::getAmountEdges()
{
    int amount = 0;
    int vertLen = vertices.size();
    for (int i = 0; i < vertLen; ++i)
    {
        for (int j = 0; j < vertLen; ++j)
        {
            if (adjMatrix[i][j] == adjMatrix[j][i] && adjMatrix[i][j] != 0)
            {
                ++amount;
            }
        }
    }
    return amount / 2;
}

int Graph::getWeight(const Vertex &v1, const Vertex &v2)
{
    int vertPos1 = getVertexPos(v1);
    int vertPos2 = getVertexPos(v2);
    return adjMatrix[vertPos1][vertPos2];
}

std::vector<Vertex> Graph::getNbrs(const Vertex &vertex)
{
    std::vector<Vertex> nbrsList;
    int pos = getVertexPos(vertex);
    if (pos != -1)
    {
        for (int i = 0, vertListSize = vertices.size(); i < vertListSize; ++i)
        {
            if (adjMatrix[pos][i] != 0)
            {
                nbrsList.push_back(vertices[i]);
            }
        }
    }
    return nbrsList;
}

void Graph::insertVertex(const Vertex &vertex)
{
    vertices.push_back(vertex);
}

void Graph::eraseVertex(const Vertex &vertex)
{
    int pos = getVertexPos(vertex);
    if (pos == -1)
    {
        return;
    }
    vertices.erase(vertices.begin() + pos);
    for (int i = pos; i < maxSize - 1; ++i)
    {
        for (int j = 0; j < maxSize; ++j)
        {
            adjMatrix[i][j] = adjMatrix[i + 1][j];
        }
    }
    for (int i = 0; i < maxSize; ++i)
    {
        for (int j = pos; j < maxSize - 1; ++j)
        {
            adjMatrix[i][j] = adjMatrix[i][j + 1];
        }
    }
    for (int i = 0; i < maxSize; ++i)
    {
        adjMatrix[maxSize - 1][i] = 0;
        adjMatrix[i][maxSize - 1] = 0;
    }
}

void Graph::insertEdge(const Vertex &v1, const Vertex &v2, int weight)
{
    int vertPos1 = getVertexPos(v1);
    int vertPos2 = getVertexPos(v2);
    if (vertPos1 == -1 || vertPos2 == -1)
    {
        return;
    }
    adjMatrix[vertPos1][vertPos2] = weight;
    adjMatrix[vertPos2][vertPos1] = weight;
}

void Graph::eraseEdge(const Vertex &v1, const Vertex &v2)
{
    int vertPos1 = getVertexPos(v1);
    int vertPos2 = getVertexPos(v2);
    if (vertPos1 == -1 || vertPos2 == -1)
    {
        return;
    }
    adjMatrix[vertPos1][vertPos2] = 0;
    adjMatrix[vertPos2][vertPos1] = 0;
}

void Graph::print()
{
    QString text;
    text += "Graph matrix adjacency\n";

    int vertLen = vertices.size();

    text += "    ";
    for (int i = 0; i < vertLen; ++i)
    {
        text += QString("%1 ").arg(i, 2);
    }
    text += "\n";

    for (int i = 0; i < vertLen; ++i)
    {
        text += QString("%1: ").arg(i, 2);
        for (int j = 0; j < vertLen; ++j)
        {
            text += QString("%1 ").arg(adjMatrix[i][j], 2);
        }
        text += "\n";
    }

    std::cout << text.toStdString() << std::endl;
}

QString Graph::floydWarshall()
{
    int vertLen = vertices.size();
    const int INF = std::numeric_limits<int>::max() / 2;

    int dist[maxSize][maxSize];
    int next[maxSize][maxSize];

    for (int i = 0; i < vertLen; ++i)
    {
        for (int j = 0; j < vertLen; ++j)
        {
            if (i == j)
            {
                dist[i][j] = 0;
                next[i][j] = j;
            }
            else if (adjMatrix[i][j] != 0)
            {
                dist[i][j] = adjMatrix[i][j];
                next[i][j] = j;
            }
            else
            {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < vertLen; ++k)
    {
        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    QString result;
    for (int i = 0; i < vertLen; ++i)
    {
        for (int j = 0; j < vertLen; ++j)
        {
            if (i != j)
            {
                result += QString("КП из вершины %1 в вершину %2: ").arg(vertices[i].id).arg(vertices[j].id);

                if (next[i][j] == -1)
                {
                    result += "нет пути\n";
                }
                else
                {
                    int u = i;
                    result += QString::number(vertices[u].id);
                    while (u != j)
                    {
                        u = next[u][j];
                        result += "-" + QString::number(vertices[u].id);
                    }
                    result += QString(" (%1);\n").arg(dist[i][j]);
                }
            }
        }
    }
    return result;
}
