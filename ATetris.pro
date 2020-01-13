QT       += core gui
QT += quickwidgets

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
    ai/ccbot.cpp \
    mode/c4wmode.cpp \
    mode/fortymode.cpp \
    mode/marathonmode.cpp \
    widget/bloodbar.cpp \
    widget/gamewidget.cpp \
    widget/nextwindow.cpp\
    config/keypressmanager.cpp \
    config/settingsmanager.cpp \
    main.cpp \
    widget/particlewidget.cpp \
    windows/botbattle.cpp \
    windows/gameoverdialog.cpp \
    windows/mainwindow.cpp \
    seq/seq.cpp \
    windows/modewindow.cpp \
    windows/settingdialog.cpp \
    tetromino/c.cpp \
    tetromino/gamemap.cpp \
    tetromino/tetromino.cpp \
    windows/singlegamewindow.cpp

HEADERS += \
    ai/ccbot.h \
    ai/coldclear.h\
    config/keypressmanager.h \
    config/settingsmanager.h \
    data/stat.h \
    mode/c4wmode.h \
    mode/fortymode.h \
    mode/marathonmode.h \
    mode/modebase.h \
    widget/bloodbar.h \
    widget/gamewidget.h \
    widget/nextwindow.h\
    widget/particlewidget.h \
    windows/botbattle.h \
    windows/gameoverdialog.h \
    windows/mainwindow.h \
    seq/seq.h \
    tetromino/c.h \
    tetromino/gamemap.h \
    tetromino/tetro.h \
    tetromino/tetromino.h \
    data/grid.h \
    windows/modewindow.h \
    windows/settingdialog.h \
    windows/singlegamewindow.h

FORMS += \
    windows/botbattle.ui \
    windows/gameoverdialog.ui \
    windows/mainwindow.ui \
    windows/modewindow.ui \
    windows/settingdialog.ui \
    windows/singlegamewindow.ui

LIBS += -L$$PWD/libs -lcold_clear

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    json/settings.json \
    theme/gbg.png

RESOURCES += \
    res.qrc

