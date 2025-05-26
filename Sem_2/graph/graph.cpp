#include "graph.h"
#include "qdebug.h"
#include <QRandomGenerator>
#include <QString>
#include <deque>
#include <iostream>
#include <limits>

Vertex::Vertex(unsigned char overrideId)
{
    x = QRandomGenerator::global()->bounded(25, 900);
    y = QRandomGenerator::global()->bounded(25, 600);
    static unsigned char newId = 0;
    if (overrideId != 0)
    {
        newId = overrideId - 1;
    }
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

void Graph::BFS(Vertex &startVertex, bool *visitedVerts)
{
    std::queue<Vertex> q;
    q.push(startVertex);
    visitedVerts[this->getVertexPos(startVertex)] = true;
    std::cout << "Vertex " << (int)startVertex.id << " visited" << std::endl;
    while (!q.empty())
    {
        Vertex currentVertex = q.front();
        q.pop();
        std::vector<Vertex> neighbors = this->getNbrs(currentVertex);
        for (const Vertex &neighbor : neighbors)
        {
            int neighborIndex = this->getVertexPos(neighbor);
            if (!visitedVerts[neighborIndex])
            {
                q.push(neighbor);
                visitedVerts[neighborIndex] = true;
                std::cout << "Vertex " << (int)neighbor.id << " visited" << std::endl;
            }
        }
    }
}

QString Graph::floydWarshall()
{
    int vertLen = vertices.size();

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

// a mess? messy! but works? work! sometimes.
void Graph::processBranch(std::deque<BBNode> &bbNodes)
{
    qDebug() << "Entering processBranch";
    int vertLen = vertices.size();

    BBNode *RootNode = nullptr;
    int bblen = bbNodes.size();
    for (int i = 0; i < bblen; ++i)
    {
        BBNode &node = bbNodes[i];
        if (!node.hasBranches)
        {
            if (RootNode == nullptr || RootNode->root > node.root)
            {
                RootNode = &node;
            }
        }
    }

    if (RootNode == nullptr)
    {
        int minsByRows[maxSize]; // d_i
        std::fill(minsByRows, minsByRows + vertLen, INF);

        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                minsByRows[i] = std::min(minsByRows[i], adj[i][j]);
            }
        }

        // reduce rows
        for (int i = 0; i < vertLen; ++i)
        {
            if (minsByRows[i] == INF)
            {
                continue;
            }
            for (int j = 0; j < vertLen; ++j)
            {
                if (adj[i][j] != INF)
                    adj[i][j] -= minsByRows[i];
            }
        }

        int minsByColumns[maxSize]; // d_j
        std::fill(minsByColumns, minsByColumns + vertLen, INF);
        for (int j = 0; j < vertLen; ++j)
        {
            for (int i = 0; i < vertLen; ++i)
            {
                minsByColumns[j] = std::min(minsByColumns[j], adj[i][j]);
            }
        }

        // reduce columns
        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                if (minsByColumns[j] == INF)
                {
                    continue;
                }
                if (adj[i][j] != INF)
                    adj[i][j] -= minsByColumns[j];
            }
        }

        int root = 0; // H_0
        root += std::accumulate(minsByRows, minsByRows + vertLen, 0);
        root += std::accumulate(minsByColumns, minsByColumns + vertLen, 0);
        qDebug() << "Root" << root;

        bbNodes.push_back(BBNode(root, -1, -1, adj));
        RootNode = &bbNodes[bbNodes.size() - 1];
    }
    else if (RootNode->asterisk)
    {
        int minsByRows[maxSize]; // d_i
        std::fill(minsByRows, minsByRows + vertLen, INF);

        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                minsByRows[i] = std::min(minsByRows[i], RootNode->adjMatrix[i][j]);
            }
        }

        // reduce rows
        for (int i = 0; i < vertLen; ++i)
        {
            if (minsByRows[i] == INF)
            {
                continue;
            }
            for (int j = 0; j < vertLen; ++j)
            {
                if (RootNode->adjMatrix[i][j] != INF)
                    RootNode->adjMatrix[i][j] -= minsByRows[i];
            }
        }

        int minsByColumns[maxSize]; // d_j
        std::fill(minsByColumns, minsByColumns + vertLen, INF);
        for (int j = 0; j < vertLen; ++j)
        {
            for (int i = 0; i < vertLen; ++i)
            {
                minsByColumns[j] = std::min(minsByColumns[j], RootNode->adjMatrix[i][j]);
            }
        }

        // reduce columns
        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                if (minsByColumns[j] == INF)
                {
                    continue;
                }
                if (RootNode->adjMatrix[i][j] != INF)
                    RootNode->adjMatrix[i][j] -= minsByColumns[j];
            }
        }
    }

    int rootIndex = 0;
    for (int i = 0; i < bbNodes.size(); i++)
    {
        if (&bbNodes[i] == RootNode)
        {
            rootIndex = i;
            qDebug() << "New root index" << rootIndex << RootNode->root << RootNode->asterisk;
            break;
        }
    }

    int maxPenalty = -1;
    int maxRow = -1, maxCol = -1;
    for (int i = 0; i < vertLen; ++i)
    {
        for (int j = 0; j < vertLen; ++j)
        {
            if (RootNode->adjMatrix[i][j] == 0)
            {
                int rowMin = INF;
                for (int k = 0; k < vertLen; ++k)
                {
                    if (k != j && RootNode->adjMatrix[i][k] < rowMin)
                    {
                        rowMin = RootNode->adjMatrix[i][k];
                    }
                }
                int colMin = INF;
                for (int k = 0; k < vertLen; ++k)
                {
                    if (k != i && RootNode->adjMatrix[k][j] < colMin)
                    {
                        colMin = RootNode->adjMatrix[k][j];
                    }
                }
                int penalty = (rowMin == INF ? 0 : rowMin) + (colMin == INF ? 0 : colMin);
                if (penalty >= maxPenalty)
                {
                    maxPenalty = penalty;
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
    }
    qDebug() << "Max penalty at (" << maxRow << "," << maxCol << ") with val " << maxPenalty;

    QString text;
    text += "CURR MATRIX\n";
    text += "    ";
    for (int i = 0; i < vertLen; ++i)
    {
        text += QString("%1 ").arg(i, 6);
    }
    text += "\n";
    for (int i = 0; i < vertLen; ++i)
    {
        text += QString("%1: ").arg(i, 6);
        for (int j = 0; j < vertLen; ++j)
        {
            text += QString("%1 ").arg(RootNode->adjMatrix[i][j], 6);
        }
        text += "\n";
    }
    std::cout << text.toStdString() << std::endl;

    int startCity = maxRow;
    int endCity = maxCol;

    // 2 branch (no include)
    {
        int tmp = RootNode->adjMatrix[startCity][endCity];
        RootNode->adjMatrix[startCity][endCity] = INF;
        int root = bbNodes[rootIndex].root + maxPenalty;

        BBNode node = BBNode(root, startCity, endCity, RootNode->adjMatrix);
        node.asterisk = true;
        node.parent = RootNode;
        bbNodes.push_back(node);
        RootNode->adjMatrix[startCity][endCity] = tmp;
    }

    // 1 branch(with include)
    for (int col = 0; col < vertLen; ++col)
    {
        RootNode->adjMatrix[startCity][col] = INF;
    }
    for (int row = 0; row < vertLen; ++row)
    {
        RootNode->adjMatrix[row][endCity] = INF;
    }

    {

        RootNode->adjMatrix[endCity][startCity] = INF;
        int minsByRows[maxSize]; // d_i
        std::fill(minsByRows, minsByRows + vertLen, INF);

        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                minsByRows[i] = std::min(minsByRows[i], RootNode->adjMatrix[i][j]);
            }
        }

        // reduce rows
        for (int i = 0; i < vertLen; ++i)
        {
            if (minsByRows[i] == INF)
            {
                continue;
            }
            for (int j = 0; j < vertLen; ++j)
            {
                if (RootNode->adjMatrix[i][j] != INF)
                    RootNode->adjMatrix[i][j] -= minsByRows[i];
            }
        }

        int minsByColumns[maxSize]; // d_j
        std::fill(minsByColumns, minsByColumns + vertLen, INF);
        for (int j = 0; j < vertLen; ++j)
        {
            for (int i = 0; i < vertLen; ++i)
            {
                minsByColumns[j] = std::min(minsByColumns[j], RootNode->adjMatrix[i][j]);
            }
        }

        // reduce columns
        for (int i = 0; i < vertLen; ++i)
        {
            for (int j = 0; j < vertLen; ++j)
            {
                if (minsByColumns[j] == INF)
                {
                    continue;
                }
                if (RootNode->adjMatrix[i][j] != INF)
                    RootNode->adjMatrix[i][j] -= minsByColumns[j];
            }
        }

        int root = bbNodes[rootIndex].root; // H_x
        for (int i = 0; i < vertLen; ++i)
        {
            if (minsByRows[i] != INF)
            {
                root += minsByRows[i];
            }
        }

        for (int i = 0; i < vertLen; ++i)
        {
            if (minsByColumns[i] != INF)
            {
                root += minsByColumns[i];
            }
        }
        BBNode node = BBNode(root, startCity, endCity, RootNode->adjMatrix);
        node.parent = RootNode;
        bbNodes.push_back(node);
    }

    RootNode->hasBranches = true;

    qDebug() << "New branches" << bbNodes[rootIndex + 1].root << bbNodes[rootIndex + 2].root;

    if (maxPenalty == 0)
    {
        return;
    }
    processBranch(bbNodes);
}

QString Graph::TSP()
{

    int vertLen = vertices.size();
    std::deque<BBNode> bbNodes;
    // 0->INF
    adj.resize(vertLen, std::vector<int>(vertLen));
    for (int i = 0; i < vertLen; ++i)
    {
        for (int j = 0; j < vertLen; ++j)
        {
            if (i == j)
                adj[i][j] = INF;
            else
                adj[i][j] = adjMatrix[i][j] == 0 ? INF : adjMatrix[i][j];
        }
    }
    processBranch(bbNodes);

    int lastInd = bbNodes.size() - 1;
    QString result;
    for (BBNode *node = &bbNodes[lastInd]; node != nullptr; node = node->parent)
    {
        qDebug() << node->start << node->end << node->root << node->asterisk;
        if (node->start >= 0)
        {
            if (node->hasBranches)
            {
                result = "->" + result;
            }
            char realVertexId = vertices[node->start].id;
            result = QString::number(realVertexId) + result;
        }
    }
    char realVertexId = vertices[bbNodes[lastInd].end].id;
    result += QString::number(realVertexId);
    result += QString("\nитого %1").arg(bbNodes[lastInd].root);
    return result;
}

