#include "mainwindow.h"
#include "infowindow.h"
#include "packetids.h"
#include <QApplication>
#include <QCheckBox>
#include <QCoreApplication>
#include <QDateTime>
#include <QGroupBox>
#include <QHeaderView>
#include <QIcon>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QProcess>
#include <QRadioButton>
#include <QSettings>
#include <QStyle>
#include <QTableWidget>
#include <QTextEdit>
#include <QTimeEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(999, 333);
    central = new QWidget(this);
    setCentralWidget(central);
    initWelcomeScreen();
    setWindowTitle("АУКРС v0");
}

MainWindow::~MainWindow()
{
}

// окно входа
void MainWindow::initWelcomeScreen()
{
    textInputWithIp = new QLineEdit(this);
    textInputWithIp->setFixedWidth(350);
    QString hint = "Введите адрес сервера в формате ip:port";
    textInputWithIp->setPlaceholderText(hint);
    textInputWithIp->setToolTip(hint);
    QHBoxLayout *hlayout = new QHBoxLayout();
    button = new QPushButton("Старт", this);
    QIcon::setThemeName(QIcon::fallbackThemeName());
    button->setIcon(QIcon::fromTheme("emblem-mounted"));
    hlayout->addStretch();
    hlayout->addWidget(textInputWithIp, 0, Qt::AlignCenter);
    hlayout->addWidget(button, 0, Qt::AlignCenter);
    hlayout->addStretch();
    connect(textInputWithIp, &QLineEdit::returnPressed, this, &MainWindow::hideWelcomeScreen);
    connect(button, &QPushButton::clicked, this, &MainWindow::hideWelcomeScreen);
    QSettings settings("QTSettings");
    QString savedIp = settings.value("serverAddress", "").toString();
    if (!savedIp.isEmpty())
    {
        textInputWithIp->setText(savedIp);
    }
    QVBoxLayout *vlayout = new QVBoxLayout(central);
    QLabel *label = new QLabel("АУКРС", this);
    label->setStyleSheet("font: 24pt; font-weight: bold;");
    label->setAlignment(Qt::AlignCenter);
    vlayout->addStretch();
    vlayout->addWidget(label, 0, Qt::AlignHCenter);
    vlayout->addSpacing(5);
    vlayout->addLayout(hlayout);
    vlayout->addStretch();
}

// убираем экран и добавляем основной + подключаемся к серверу
void MainWindow::hideWelcomeScreen()
{
    QStringList parts = textInputWithIp->text().split(":");
    if (parts.length() != 2 || parts[1].length() > 5 || parts[1].length() < 3)
    {
        textInputWithIp->setStyleSheet("background-color: darkred");
        return;
    }
    QSettings settings("QTSettings");
    settings.setValue("serverAddress", textInputWithIp->text());
    button->deleteLater();
    textInputWithIp->deleteLater();
    delete central->layout();
    initMainScreen();
    initMenuBar();
    QString address = parts[0];
    quint16 port = parts[1].toUShort();
    network = new Network();
    connect(network, &Network::packetRecv, this, &MainWindow::onPacketRecv);
    connect(network, &Network::badConnection, this, &MainWindow::onBadConnection);
    logToPanel("Идёт подключение к серверу...");
    network->connectToServer(address, port);
}

// меню полоски вверху программы
void MainWindow::initMenuBar()
{
    menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("Программа");
    fileMenu->addAction("Выход", this, QApplication::exit);
    fileMenu->addAction("Перезапуск", this, &MainWindow::restartApp);
    menuBar->addMenu(fileMenu);
    // QMenu *testMenu = new QMenu("Тест");
    // menuBar->addMenu(testMenu);
    layout()->setMenuBar(menuBar);

    QCheckBox *hideOffedArduinosCheckBox = new QCheckBox("Скрывать неактивные ардуино", this);
    hideOffedArduinosCheckBox->setGeometry(270, 0, 400, 35);
    layout()->addWidget(hideOffedArduinosCheckBox);
    connect(hideOffedArduinosCheckBox, &QCheckBox::stateChanged, this, &MainWindow::checkBoxChanged);
}

// на чекбокс кликнули
void MainWindow::checkBoxChanged(int state)
{
    bool checked = state == Qt::Checked;
    int rowCount = tableWidget->rowCount();
    for (int row = 0; row < rowCount; ++row)
    {
        QTableWidgetItem *statusItem = tableWidget->item(row, 2);
        if (statusItem->text() == "Оффлайн")
        {
            tableWidget->setRowHidden(row, checked);
        }
    }
}

// перезапустить программу
void MainWindow::restartApp()
{
    QProcess::startDetached(QCoreApplication::applicationFilePath(), QCoreApplication::arguments());
    QApplication::exit();
}

// в главный экран входит таблица + лог панель
void MainWindow::initMainScreen()
{
    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(7);
    tableWidget->setHorizontalHeaderLabels(
        {"ID", "Заметка", "Статус", "Возраст", "Темп. помещения", "Лежит", "Действия"});
    tableWidget->horizontalHeaderItem(0)->setToolTip("ID Arduino");
    tableWidget->horizontalHeaderItem(0)->setIcon(QIcon::fromTheme("cpu"));
    tableWidget->horizontalHeaderItem(1)->setToolTip("Заметка для себя");
    tableWidget->horizontalHeaderItem(1)->setIcon(QIcon::fromTheme("emblem-question"));
    tableWidget->horizontalHeaderItem(2)->setToolTip("Статус с Arduino");
    tableWidget->horizontalHeaderItem(2)->setIcon(QIcon::fromTheme("package-new"));
    tableWidget->horizontalHeaderItem(3)->setToolTip("Возраст устанавливается на стороне Arduino или на сервере");
    tableWidget->horizontalHeaderItem(3)->setIcon(QIcon::fromTheme("food-cake"));
    tableWidget->horizontalHeaderItem(4)->setToolTip("Температура в помещении");
    tableWidget->horizontalHeaderItem(4)->setIcon(QIcon::fromTheme("colorfx"));
    tableWidget->horizontalHeaderItem(5)->setToolTip("Лежит ли?");
    tableWidget->horizontalHeaderItem(5)->setIcon(QIcon::fromTheme("data-information"));
    tableWidget->horizontalHeaderItem(6)->setToolTip("Доступные действия");
    tableWidget->horizontalHeaderItem(6)->setIcon(QIcon::fromTheme("financial-list"));
    tableWidget->setColumnWidth(1, 150);
    tableWidget->setColumnWidth(4, 170);
    tableWidget->setColumnWidth(5, 85);
    tableWidget->showGrid();
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(2, 5, 2, 5);
    layout->addWidget(tableWidget, 2);
    logPanel = new QTextEdit();
    logPanel->setReadOnly(true);
    layout->addWidget(logPanel, 1);
    central->setLayout(layout);
    setCentralWidget(central);
}

// пишет в лог панель с таймштампом
void MainWindow::logToPanel(QString text, bool redText)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString lineText = "[" + timestamp + "] " + text;
    if (!redText)
    {
        logPanel->append(lineText);
    }
    else
    {
        logPanel->append("<span style='color: red'>" + lineText + "</span>");
    }
}

void MainWindow::onBadConnection()
{
    logToPanel("Ошибка подключения :(", true);
}

// обработка пакета
void MainWindow::onPacketRecv(qint16 id, QStringList args)
{
    switch (id)
    {
    case PacketID_HI: {
        logToPanel("Подключение успешно!");
    }
    break;
    case PacketID_INIT_ROW: {
        tableWidget->insertRow(tableWidget->rowCount());
        int row = tableWidget->rowCount() - 1;
        bool isOffline = false;
        for (int i = 0; i < 6; ++i)
        {
            if (i == 1)
            {
                // ячейка заметка, можно редактировать
                QLineEdit *noteLineEdit = new QLineEdit();
                tableWidget->setCellWidget(row, i, noteLineEdit);
                noteLineEdit->setText(args[i]);
                connect(noteLineEdit, &QLineEdit::editingFinished, this, [=]() {
                    QString id = tableWidget->item(row, 0)->text();
                    network->sendPacket(PacketID_EDIT_NOTE, id + ";" + noteLineEdit->text());
                });
            }
            else
            {
                QTableWidgetItem *item = new QTableWidgetItem(args[i]);
                if (isOffline && i > 3)
                {
                    item->setForeground(QBrush(Qt::gray));
                }
                else if (args[i] == "Оффлайн")
                {
                    isOffline = true;
                    item->setForeground(QBrush(Qt::red));
                }
                tableWidget->setItem(row, i, item);
            }
        }
        QPushButton *moreButton = new QPushButton("Подробнее");
        connect(moreButton, &QPushButton::clicked, this, [=]() {
            QString id = tableWidget->item(row, 0)->text();
            network->sendPacket(PacketID_GET_FULL_INFO, id + ";За неделю");
        });

        QPushButton *feedButton = new QPushButton("Расчёт корма");
        connect(feedButton, &QPushButton::clicked, this, [=]() {
            QString ageText = tableWidget->item(row, 3)->text();
            int monthNum = ageText.leftRef(ageText.indexOf("м")).toInt();
            int dayNum =
                ageText.midRef(ageText.indexOf(" ") + 1, ageText.indexOf("д") - ageText.indexOf(" ") - 1).toInt();
            int totalDays = monthNum * 30 + dayNum;
            float kg = 0.2 + (totalDays / 30.0) * 0.22;
            QMessageBox msgBox;
            msgBox.setText("Расчёт корма на день 🐮");
            msgBox.setInformativeText(QString::number(kg, 'g', 2) + " кг");
            msgBox.exec();
        });

        QWidget *cellWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(cellWidget);
        layout->setSpacing(0);
        layout->addWidget(moreButton);
        layout->addWidget(feedButton);
        layout->setContentsMargins(0, 0, 0, 0);
        cellWidget->setLayout(layout);

        tableWidget->setCellWidget(tableWidget->rowCount() - 1, 6, cellWidget);
        logToPanel("Строка " + args[0] + " добавлена");
    }
    break;
    case PacketID_UPDATE_ROW_CELL_VALUE: {
        int columnCount = tableWidget->columnCount();
        int changeCol = -1;
        for (int col = 0; col < columnCount; ++col)
        {
            QTableWidgetItem *headerItem = tableWidget->horizontalHeaderItem(col);
            if (headerItem && headerItem->text() == args[1])
            {
                changeCol = col;
                break;
            }
        }
        for (int row = 0; row < tableWidget->rowCount(); ++row)
        {
            QTableWidgetItem *item = tableWidget->item(row, 0);
            if (item && item->text() == args[0])
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(args[2]);
                if (args[2] == "Оффлайн")
                {
                    newItem->setForeground(QBrush(Qt::red));
                }
                tableWidget->setItem(row, changeCol, newItem);
                return;
            }
        }
    }
    break;
    case PacketID_SEND_FULL_INFO: {
        InfoWindow *infoWindow = new InfoWindow(args, network);
        infoWindow->show();
    }
    break;
    }
}
