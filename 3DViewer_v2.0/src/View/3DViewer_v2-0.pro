QT       += core gui openglwidgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(QtGifImage/src/gifimage/qtgifimage.pri) # подключение библиотеки для работы с gif

SOURCES += \
    ../main.cc \
    ../Model/Parser/parser.cc \
    ../Model/Affine/affine.cc \
    ../Model/Facade/facade.cc \
    ../Model/Figure/figure.cc \
    ../Controller/controller.cc \
    ../Model/Strategy/strategy.cc \
    ../Model/Command/command.cc \
    mainwindow.cc

HEADERS += \
    ../Model/Parser/parser.h \
    ../Model/Affine/affine.h \
    ../Model/Facade/facade.h \
    ../Model/Figure/figure.h \
    ../Controller/controller.h \
    ../Model/Strategy/strategy.h \
    ../Model/Command/command.h \
    mainwindow.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
