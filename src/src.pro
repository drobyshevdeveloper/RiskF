#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T12:32:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RiskF
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



LC_VERSION="1.0.3"
VERSION=$${LC_VERSION}

# Для работы отладочных функций закомментируйте следующую строку
# иначе вывод отладочной информации будет заблокирован
# DEFINES += QT_NO_DEBUG_OUTPUT


# Store intermedia stuff somewhere else
GENERATED_DIR = ../generated/RiskF


# Store intermedia stuff somewhere else
OBJECTS_DIR = $${GENERATED_DIR}/obj
MOC_DIR = $${GENERATED_DIR}/moc
RCC_DIR = $${GENERATED_DIR}/rcc
UI_DIR = $${GENERATED_DIR}/ui
UI_HEADERS_DIR = $${GENERATED_DIR}/ui
UI_SOURCES_DIR = $${GENERATED_DIR}/ui


INCLUDEPATH += \
        lib \
        lib/debug \
        main




##################################################################
# main
SOURCES += \
        main/main.cpp \
        main/mainwindow.cpp


HEADERS += \
        main/mainwindow.h


##################################################################
# Library
HEADERS += \
        lib/debug/rl_debug.h \
        lib/rl_settings.h

SOURCES += \
        lib/rl_settings.cpp
