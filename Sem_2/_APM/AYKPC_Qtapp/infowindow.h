#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "network.h"

class InfoWindow : public QWidget
{
    Q_OBJECT
  public:
    explicit InfoWindow(QStringList &args, Network* network);

  public slots:
    void onCloseButtonClicked();
    void onUpdateButtonClicked();
    void onTimeLimitComboBoxChanged(QString newTimeLimit);

  private:
    Network *network;
    QString arduinoId;
    QString timeLimit;

  signals:
};

#endif // INFOWINDOW_H
