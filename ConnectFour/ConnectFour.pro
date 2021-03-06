QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += sdk_no_version_check

ICON = img/logo.icns

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    boardpanel.cpp \
    creditsdialog.cpp \
    field.cpp \
    game.cpp \
    gamefinishdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp

HEADERS += \
    board.h \
    boardpanel.h \
    constants.h \
    creditsdialog.h \
    field.h \
    game.h \
    gamefinishdialog.h \
    mainwindow.h \
    settingsdialog.h

FORMS += \
    creditsdialog.ui \
    gamefinishdialog.ui \
    mainwindow.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    images.qrc
