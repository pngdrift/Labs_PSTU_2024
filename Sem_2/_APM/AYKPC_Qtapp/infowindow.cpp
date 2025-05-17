#include "infowindow.h"
#include "packetids.h"
#include <QComboBox>
#include <QEasingCurve>
#include <QPushButton>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

// окно подробной статистики
InfoWindow::InfoWindow(QStringList &args, Network *n) : QWidget()
{
    network = n;
    arduinoId = args[0];
    timeLimit = args[3];

    setWindowTitle("InfoWindow");
    resize(750, 400);
    setMinimumSize(750, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *headerLabel = new QLabel("Статистика " + args[0], this);
    headerLabel->setStyleSheet("font-weight: bold;");

    QString statsText = "Всего время отдыха (лежания): " + args[1];
    statsText += "\tМаксимальное время отдыха: " + args[2];

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(headerLabel);
    QComboBox *timeLimitComboBox = new QComboBox(this);
    timeLimitComboBox->addItem("За час");
    timeLimitComboBox->addItem("За сутки");
    timeLimitComboBox->addItem("За неделю");
    timeLimitComboBox->addItem("За месяц");
    timeLimitComboBox->addItem("За всё время");
    timeLimitComboBox->setCurrentText(args[3]);
    connect(timeLimitComboBox, &QComboBox::currentTextChanged, this, &InfoWindow::onTimeLimitComboBoxChanged);
    headerLayout->addWidget(timeLimitComboBox);

    layout->addLayout(headerLayout);

    QLabel *label = new QLabel(statsText, this);
    layout->addWidget(label);

    QLineSeries *series = new QLineSeries();
    int tempLen = args[4].toInt() * 2;
    for (int i = 0; i < tempLen; i += 2)
    {
        qint64 a = args[5 + i].toLongLong();
        float b = args[5 + i + 1].toFloat();
        series->append(a, b);
    }
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setBackgroundVisible(false);
    chart->setTheme(QChart::ChartThemeDark);
    chart->addSeries(series);
    chart->setTitle("Температура в помещении (℃)");
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setTickCount(7);
    axisX->setFormat("dd MMM<br> hh:mm");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *updateButton = new QPushButton("Обновить");
    updateButton->setIcon(QIcon::fromTheme("system-reboot"));
    buttonsLayout->addWidget(updateButton);
    connect(updateButton, &QPushButton::clicked, this, &InfoWindow::onUpdateButtonClicked);

    QPushButton *closeButton = new QPushButton("Закрыть");
    closeButton->setIcon(QIcon::fromTheme("dialog-close"));
    buttonsLayout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, this, &InfoWindow::onCloseButtonClicked);

    layout->addLayout(buttonsLayout);
}

void InfoWindow::onCloseButtonClicked()
{
    deleteLater();
}

void InfoWindow::onUpdateButtonClicked()
{
    network->sendPacket(PacketID_GET_FULL_INFO, arduinoId + ";" + timeLimit);
    deleteLater();
}

void InfoWindow::onTimeLimitComboBoxChanged(QString newTimeLimit)
{
    network->sendPacket(PacketID_GET_FULL_INFO, arduinoId + ";" + newTimeLimit);
    deleteLater();
}
