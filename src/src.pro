#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T12:32:38
#
#-------------------------------------------------

QT       += core gui widgets

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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



LC_VERSION="1.0.41"
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
        actions     \
        lib         \
        lib/actions \
        lib/debug   \
        lib/engine  \
        lib/gui     \
        lib/modification \
        lib/information \
        lib/geom    \
        main        \
        ui          \
        ui/forms    \
        ../res


RESOURCES += ../res/icons/icons.qrc


FORMS += \
        ui/forms/ru_coordinatewidget.ui


##################################################################
# Library
HEADERS += \
        lib/debug/rl_debug.h \
        lib/rl_settings.h \
        lib/gui/rl_dialogfactoryinterface.h\
        lib/gui/rl_dialogfactory.h \
        lib/engine/rg_undoable.h \
        lib/engine/rg_entity.h \
        lib/engine/rg_entitycontainer.h \
        lib/engine/rg_document.h \
        lib/engine/rg_graphic.h \
        lib/gui/rg_graphicview.h \
        lib/actions/rg_snapper.h \
        lib/actions/rg_actioninterface.h \
        lib/actions/rg_previewactioninterface.h \
        lib/actions/rg_preview.h \
        lib/engine/rg.h \
        lib/gui/rg_eventhandler.h \
        lib/engine/rg_atomicentity.h \
        lib/engine/rg_line.h \
        lib/engine/rg_vector.h \
        lib/engine/rg_painter.h \
        lib/engine/rg_painterqt.h\
        lib/gui/rg_coordinateevent.h \
        lib/modification/rg_selection.h \
        lib/engine/rg_pen.h \
        lib/engine/rg_overlayrect.h \
        lib/information/rg_information.h \
        lib/geom/geom.h \
        lib/engine/rg_marker.h \
        lib/modification/rg_modification.h \
        lib/engine/rg_undo.h \
        lib/engine/rg_undogroup.h \
        lib/engine/rg_rectangle.h \
        lib/engine/rg_polygon.h
SOURCES += \
        lib/rl_settings.cpp \
        lib/gui/rl_dialogfactory.cpp \
        lib/engine/rg_undoable.cpp \
        lib/engine/rg_entity.cpp \
        lib/engine/rg_entitycontainer.cpp \
        lib/engine/rg_document.cpp \
        lib/engine/rg_graphic.cpp \
        lib/gui/rg_graphicview.cpp \
        lib/actions/rg_snapper.cpp \
        lib/actions/rg_actioninterface.cpp \
        lib/actions/rg_previewactioninterface.cpp \
        lib/actions/rg_preview.cpp \
        lib/engine/rg.cpp \
        lib/gui/rg_eventhandler.cpp \
        lib/engine/rg_atomicentity.cpp \
        lib/engine/rg_line.cpp \
        lib/engine/rg_vector.cpp \
        lib/engine/rg_painter.cpp \
        lib/engine/rg_painterqt.cpp\
        lib/gui/rg_coordinateevent.cpp \
        lib/modification/rg_selection.cpp \
        lib/engine/rg_pen.cpp \
        lib/engine/rg_overlayrect.cpp \
        lib/information/rg_information.cpp \
        lib/geom/geom.cpp \
        lib/engine/rg_marker.cpp \
        lib/modification/rg_modification.cpp \
        lib/engine/rg_undo.cpp \
        lib/engine/rg_undogroup.cpp \
        lib/engine/rg_rectangle.cpp \
        lib/engine/rg_polygon.cpp


##################################################################
# User Interface
HEADERS += \
        ui/rs_centralwidget.h \
        ui/rs_actionfactory.h \
        ui/rs_actionhandler.h \
        ui/rs_actiongroupmanager.h \
        ui/rs_widgetfactory.h \
        ui/rs_dialogfactory.h \
        ui/rs_graphicview.h \
        ui/rs_scrollbar.h \
        ui/forms/ru_coordinatewidget.h

SOURCES += \
        ui/rs_centralwidget.cpp \
        ui/rs_actionfactory.cpp \
        ui/rs_actionhandler.cpp \
        ui/rs_actiongroupmanager.cpp \
        ui/rs_widgetfactory.cpp \
        ui/rs_dialogfactory.cpp \
        ui/rs_graphicview.cpp \
        ui/rs_scrollbar.cpp \
        ui/forms/ru_coordinatewidget.cpp


##################################################################
# main
HEADERS += \
        main/rf_mainwindow.h \
        main/ru_dialogfactory.h \
        main/ru_mdiwindow.h

SOURCES += \
        main/main.cpp \
        main/rf_mainwindow.cpp \
        main/ru_dialogfactory.cpp \
        main/ru_mdiwindow.cpp



##################################################################
# Actions
HEADERS += \
        actions/rg_actiondrawline.h \
        actions/rg_actiondefault.h \
        actions/rg_actionzoom.h \
        actions/rg_actionzoompan.h \
        actions/rg_actionundo.h \
        actions/rg_actiondrawrectangle.h \
        actions/rg_actiondrawpolygon.h

SOURCES += \
        actions/rg_actiondrawline.cpp \
        actions/rg_actiondefault.cpp \
        actions/rg_actionzoom.cpp \
        actions/rg_actionzoompan.cpp \
        actions/rg_actionundo.cpp \
        actions/rg_actiondrawrectangle.cpp \
        actions/rg_actiondrawpolygon.cpp
