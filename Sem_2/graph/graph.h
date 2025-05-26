#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <deque>
#include <queue>
#include <vector>

class Vertex
{
  public:
    Vertex(unsigned char overrideId = 0);
    short int x, y;
    unsigned char id;
    bool operator==(const Vertex &other) const
    {
        return id == other.id;
    }
};

constexpr int maxSize = 20;
constexpr int INF = 1e4;

struct BBNode
{
    int root;
    short int start;
    short int end;
    bool hasBranches;
    std::vector<std::vector<int>> adjMatrix;
    bool asterisk; //*
    BBNode *parent;
    BBNode(int r, short int s, short int e, std::vector<std::vector<int>> a) : root(r), start(s), end(e), adjMatrix(a)
    {
        asterisk = false;
        parent = nullptr;
    }
};

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
    void BFS(Vertex &startVertex, bool *visitedVerts);
    QString floydWarshall();
    QString TSP();
    //  private:
    std::vector<Vertex> vertices;
    int adjMatrix[maxSize][maxSize];

  private:
    void processBranch(std::deque<BBNode> &bbNodes);
    std::vector<std::vector<int>> adj; // tsp
};

#endif // GRAPH_H
