QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    glwidget4graph.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    glwidget4graph.h \
    graph.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
