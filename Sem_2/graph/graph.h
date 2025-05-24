#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <vector>

class Vertex
{
  public:
    Vertex();
    short int x, y;
    unsigned char id;
    bool operator==(const Vertex &other) const
    {
        return id == other.id;
    }
};

constexpr int maxSize = 20;

class Graph // неориентированный взвешенный
{
  public:
    Graph();
    int getVertexPos(const Vertex &);
    const Vertex *getVertexById(unsigned char id);
    int getAmountEdges();
    int getWeight(const Vertex &v1, const Vertex &v2);
    std::vector<Vertex> getNbrs(const Vertex &);
    void insertVertex(const Vertex &);
    void eraseVertex(const Vertex &vertex);
    void insertEdge(const Vertex &v1, const Vertex &c2, int weight);
    void eraseEdge(const Vertex &v1, const Vertex &v2);
    void print();
    QString floydWarshall();
    //  private:
    std::vector<Vertex> vertices;
    int adjMatrix[maxSize][maxSize];
};

#endif // GRAPH_H
