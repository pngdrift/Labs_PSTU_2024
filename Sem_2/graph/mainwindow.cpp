#include "mainwindow.h"
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QIntValidator>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1000, 700);
    central = new QWidget(this);
    setCentralWidget(central);
    graph = new Graph();
    openGlW = new GLWidget4Graph(this, graph);
    QGridLayout *grid = new QGridLayout();
    grid->setContentsMargins(0, 3, 0, 0);
    grid->addWidget(openGlW, 0, 0);
    central->setLayout(grid);
    initMenuBar();

    // initGraph11();
    initGraphTSP();
    graph->print();
    bool visitedVerts[7];
    // graph->BFS(graph->vertices[6], visitedVerts);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuBar()
{
    QMenuBar *menuBar = new QMenuBar();
    QMenu *treeMenu = new QMenu("Неориентированный &граф");
    treeMenu->addSection("Вершина");
    treeMenu->addAction("+Добавить", this, &MainWindow::addVertex);
    treeMenu->addAction("-Удалить", this, &MainWindow::deleteVertex);
    treeMenu->addSection("Ребро");
    treeMenu->addAction("+Добавить", this, &MainWindow::addEdge);
    treeMenu->addAction("-Удалить", this, &MainWindow::deleteEdge);
    treeMenu->addSection("Алгоритмы");
    treeMenu->addAction("Алгоритм Флойда", this, &MainWindow::answerBy);
    treeMenu->addAction("Задача комивояжера", this, &MainWindow::answerTSP);
    treeMenu->addSection("Заготовленные графы");
    treeMenu->addAction("Вариант 11", this, &MainWindow::initGraph11);
    treeMenu->addAction("Для коммивояжера", this, &MainWindow::initGraphTSP);
    treeMenu->addAction("Пустой", this, &MainWindow::clearGraph);
    menuBar->addMenu(treeMenu);
    layout()->setMenuBar(menuBar);
}

void MainWindow::addVertex()
{
    if (graph->vertices.size() == 20)
    {
        QMessageBox msgBox(this);
        msgBox.setText("Достигнут лимит на вершины");
        msgBox.exec();
    }
    graph->insertVertex(Vertex());
    openGlW->redraw();
}

void MainWindow::deleteVertex()
{
    QMessageBox msgBox(this);
    msgBox.setText("Чтобы удалить вершину, надо кликнуть ПКМ по ней");
    msgBox.exec();
}

void MainWindow::addEdge()
{
    QDialog dialog(this);
    QPushButton button("OK", &dialog);
    QLineEdit input(&dialog);
    input.setText("10");
    input.setPlaceholderText("Вес...");
    input.setToolTip("Вес ребра");
    input.setValidator(new QIntValidator(0, 1000, this));
    input.setMaxLength(4);
    input.setFixedSize(50, 30);
    QComboBox vertex1Combo(&dialog);
    QComboBox vertex2Combo(&dialog);
    int vertLen = graph->vertices.size();
    for (int i = 0; i < vertLen; ++i)
    {
        const Vertex &v = graph->vertices[i];
        vertex1Combo.addItem(QString::number(v.id));
        vertex2Combo.addItem(QString::number(v.id));
    }
    QGridLayout grid;
    QLabel info("Добавления ребра\nдля вершин:");
    grid.addWidget(&info, 0, 3);
    grid.addWidget(&vertex1Combo, 1, 0);
    grid.addWidget(&vertex2Combo, 1, 1);
    grid.addWidget(&input, 1, 2);
    grid.addWidget(&button, 1, 3);
    dialog.setLayout(&grid);

    connect(&button, &QPushButton::clicked, this, [&, this]() {
        const Vertex *v1 = graph->getVertexById(vertex1Combo.currentText().toInt());
        const Vertex *v2 = graph->getVertexById(vertex2Combo.currentText().toInt());
        if (v1 == nullptr || v2 == nullptr || v1 == v2)
        {
            return;
        }
        const int weight = input.text().toInt();
        graph->insertEdge(*v1, *v2, weight);
        openGlW->redraw();
        dialog.close();
    });

    dialog.exec();
}

void MainWindow::deleteEdge()
{
    QDialog dialog(this);
    QPushButton button("OK", &dialog);
    QComboBox vertex1Combo(&dialog);
    QComboBox vertex2Combo(&dialog);
    int vertLen = graph->vertices.size();
    for (int i = 0; i < vertLen; ++i)
    {
        const Vertex &v = graph->vertices[i];
        vertex1Combo.addItem(QString::number(v.id));
        vertex2Combo.addItem(QString::number(v.id));
    }
    QGridLayout grid;
    QLabel info("Удаление ребра\nу вершин:");
    grid.addWidget(&info, 0, 2);
    grid.addWidget(&vertex1Combo, 1, 0);
    grid.addWidget(&vertex2Combo, 1, 1);
    grid.addWidget(&button, 1, 2);
    dialog.setLayout(&grid);

    connect(&button, &QPushButton::clicked, this, [&, this]() {
        const Vertex *v1 = graph->getVertexById(vertex1Combo.currentText().toInt());
        const Vertex *v2 = graph->getVertexById(vertex2Combo.currentText().toInt());
        if (v1 == nullptr || v2 == nullptr || v1 == v2)
        {
            return;
        }
        graph->eraseEdge(*v1, *v2);
        openGlW->redraw();
        dialog.close();
    });

    dialog.exec();
}

void MainWindow::answerBy()
{
    graph->print();
    QString answer = graph->floydWarshall();
    QMessageBox msgBox;
    msgBox.setText("Алгоритм Флойда");
    msgBox.setInformativeText(answer);
    msgBox.exec();
}

void MainWindow::answerTSP()
{
    graph->print();
    QString answer = graph->TSP();
    QMessageBox msgBox;
    msgBox.setText("Задача Коммивояжера");
    msgBox.setInformativeText(answer);
    msgBox.exec();
}

void MainWindow::initGraph11()
{
    clearGraph();
    Vertex v1(1), v2, v3, v4, v5, v6, v7;
    graph->insertVertex(v1);
    graph->insertVertex(v2);
    graph->insertVertex(v3);
    graph->insertVertex(v4);
    graph->insertVertex(v5);
    graph->insertVertex(v6);
    graph->insertVertex(v7);
    graph->insertEdge(v3, v6, 5);
    graph->insertEdge(v6, v7, 19);
    graph->insertEdge(v7, v2, 23);
    graph->insertEdge(v2, v4, 17);
    graph->insertEdge(v4, v1, 26);
    graph->insertEdge(v1, v5, 9);
    graph->insertEdge(v5, v3, 13);
    graph->insertEdge(v5, v7, 30);
    graph->insertEdge(v6, v4, 42);
}

void MainWindow::initGraphTSP()
{
    clearGraph();
    Vertex v1(1), v2, v3, v4, v5, v6;
    graph->insertVertex(v1);
    graph->insertVertex(v2);
    graph->insertVertex(v3);
    graph->insertVertex(v4);
    graph->insertVertex(v5);
    graph->insertVertex(v6);

    graph->insertEdge(v1, v2, 97);
    graph->insertEdge(v1, v3, 60);
    graph->insertEdge(v1, v4, 73);
    graph->insertEdge(v1, v5, 17);
    graph->insertEdge(v1, v6, 52);

    graph->insertEdge(v2, v3, 41);
    graph->insertEdge(v2, v4, 52);
    graph->insertEdge(v2, v5, 90);
    graph->insertEdge(v2, v6, 30);

    graph->insertEdge(v3, v4, 21);
    graph->insertEdge(v3, v5, 35);
    graph->insertEdge(v3, v6, 41);

    graph->insertEdge(v4, v5, 95);
    graph->insertEdge(v4, v6, 46);

    graph->insertEdge(v5, v6, 81);


    // Vertex v1(1), v2, v3, v4;
    // graph->insertVertex(v1);
    // graph->insertVertex(v2);
    // graph->insertVertex(v3);
    // graph->insertVertex(v4);

    // graph->insertEdge(v1, v2, 4);
    // graph->insertEdge(v1, v3, 4);
    // graph->insertEdge(v1, v4, 9);

    // graph->insertEdge(v2, v3, 6);
    // graph->insertEdge(v2, v4, 2);

    // graph->insertEdge(v3, v4, 3);
}

void MainWindow::clearGraph()
{
    while (graph->vertices.size() > 0)
    {
        graph->eraseVertex(graph->vertices[0]);
    }
    openGlW->redraw();
}
