#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "network.h"
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void hideWelcomeScreen();
    void restartApp();

  private:
    QWidget *central;
    QPushButton *button;
    QMenuBar *menuBar;
    QLineEdit *textInputWithIp;
    QTableWidget *tableWidget;
    QTextEdit *logPanel;
    Network *network;

    void initMenuBar();
    void initWelcomeScreen();
    void checkBoxChanged(int state);
    void initMainScreen();
    void onBadConnection();
    void onPacketRecv(qint16 id, QStringList args);
    void logToPanel(QString text, bool redText = false);
};
#endif // MAINWINDOW_H
