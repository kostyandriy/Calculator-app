QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH +=

SOURCES += \
    ../C_source/valid.c \
    ../C_source/stack.c \
    ../C_source/parse.c \
    ../C_source/notation.c \
    ../C_source/credit.c \
    ../C_source/calculate.c \
    form.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp 

HEADERS += \
    ../C_source/Calc.h \
    form.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    form.ui \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SmartCalc..pro.user \
    SmartCalc.pro.user \
    untitled.pro.user.767fe4a
