#include "mainwindow.h"
#include "treepainter.h"
#include <QApplication>
#include <QCheckBox>
#include <QDialog>
#include <QDoubleValidator>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1111, 700);
    central = new QWidget(this);
    setCentralWidget(central);

    openGlW = new GLWidget(new TreePainter(), this);
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(openGlW, 0, 0);
    central->setLayout(grid);

    initMenuBar();

    binTree = new Tree();
    reinitTree();
    Traverse(binTree->rootNode);
}

MainWindow::~MainWindow()
{
    binTree->clear();
}

void MainWindow::initMenuBar()
{
    QMenuBar *menuBar = new QMenuBar();
    QMenu *treeMenu = new QMenu("&Дерево");
    treeMenu->addAction("Пересоздать", this, &MainWindow::reinitTree);
    treeMenu->addAction("Добавить узел", this, &MainWindow::addNode);
    // treeMenu->addAction("Удалить узел", this, &MainWindow::removeNode);
    treeMenu->addAction("Сделать идеально сбалансированным", this, &MainWindow::balanceTree);
    menuBar->addMenu(treeMenu);
    layout()->setMenuBar(menuBar);
    minElemLabel = new QLabel("min", this);
    minElemLabel->setGeometry(500, 0, 200, 30);
}

void MainWindow::reinitTree()
{
    binTree->clear();
    for (int i = 0; i < 25; ++i)
    {
        double d = (QRandomGenerator::global()->bounded(125) + 1) * 0.9;
        binTree->addElement(d, binTree->rootNode);
    }
    openGlW->redraw(binTree->rootNode);
    printMinElem();
}

void MainWindow::addNode()
{
    QDialog dialog(this);
    QLineEdit input(&dialog);
    input.setValidator(new QDoubleValidator(0, 1000, 1, this));
    input.setMaxLength(4);
    connect(&input, &QLineEdit::returnPressed, this, [&input, this, &dialog]() {
        double elem = input.text().toDouble();
        binTree->addElement(elem, binTree->rootNode);
        dialog.close();
    });
    dialog.exec();
    openGlW->redraw(binTree->rootNode);
    printMinElem();
}

void MainWindow::balanceTree()
{
    binTree->makeBalance();
    openGlW->redraw(binTree->rootNode);
}

void MainWindow::printMinElem()
{
    double elem = binTree->getMinNode()->data;
    minElemLabel->setText("Минимальный элемент: " + QString::number(elem));
}
