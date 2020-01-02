QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    config/keypressmanager.cpp \
    config/settingsmanager.cpp \
    main.cpp \
    windows/mainwindow.cpp \
    mode/gamemode.cpp \
    seq/seq.cpp \
    windows/modewindow.cpp \
    windows/settingsWindow.cpp \
    windows/startwindow.cpp \
    tetromino/c.cpp \
    tetromino/gamemap.cpp \
    tetromino/linecleartype.cpp \
    tetromino/tetromino.cpp \
    widget/nextwidnow.cpp

HEADERS += \
    config/keypressmanager.h \
    config/settingsmanager.h \
    windows/mainwindow.h \
    mode/gamemode.h \
    seq/seq.h \
    tetromino/c.h \
    tetromino/gamemap.h \
    tetromino/linecleartype.h \
    tetromino/tetro.h \
    tetromino/tetromino.h \
    data/grid.h \
    windows/modewindow.h \
    windows/settingsWindow.h \
    windows/startwindow.h \
    widget/nextwidnow.h

FORMS += \
    windows/mainwindow.ui \
    windows/modewindow.ui \
    windows/settingsWindow.ui \
    windows/startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    json/settings.json

RESOURCES += \
    res.qrc
