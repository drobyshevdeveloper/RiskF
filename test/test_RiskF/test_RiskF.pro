#-------------------------------------------------
#
# Project created by QtCreator 2019-01-20T22:55:25
#
#-------------------------------------------------

QT       += testlib core widgets

QT       += gui

TARGET = tst_test_rg_entity
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Store intermedia stuff somewhere else
GENERATED_DIR = ../generated/Test


# Store intermedia stuff somewhere else
OBJECTS_DIR = $${GENERATED_DIR}/obj
MOC_DIR = $${GENERATED_DIR}/moc
RCC_DIR = $${GENERATED_DIR}/rcc
UI_DIR = $${GENERATED_DIR}/ui
UI_HEADERS_DIR = $${GENERATED_DIR}/ui
UI_SOURCES_DIR = $${GENERATED_DIR}/ui

FORMS += \
        ../../src/ui/forms/ru_coordinatewidget.ui \
        ../../src/ui/forms/ru_informationwidget.ui



INCLUDEPATH += \
        ../../src/actions     \
        ../../src/lib         \
        ../../src/lib/actions \
        ../../src/lib/debug   \
        ../../src/lib/engine  \
        ../../src/lib/gui     \
        ../../src/lib/modification \
        ../../src/lib/information \
        ../../src/lib/geom    \
        ../../src/main        \
        ../../src/ui          \
        ../../src/ui/forms    \
        ../../res


SOURCES += \
        ../../src/lib/rl_settings.cpp \
        ../../src/lib/gui/rl_dialogfactory.cpp \
        ../../src/lib/engine/rg_undoable.cpp \
        ../../src/lib/engine/rg_entity.cpp \
        ../../src/lib/engine/rg_entitycontainer.cpp \
        ../../src/lib/engine/rg_document.cpp \
        ../../src/lib/engine/rg_graphic.cpp \
        ../../src/lib/gui/rg_graphicview.cpp \
        ../../src/lib/actions/rg_snapper.cpp \
        ../../src/lib/actions/rg_actioninterface.cpp \
        ../../src/lib/actions/rg_previewactioninterface.cpp \
        ../../src/lib/actions/rg_preview.cpp \
        ../../src/lib/engine/rg.cpp \
        ../../src/lib/gui/rg_eventhandler.cpp \
        ../../src/lib/engine/rg_atomicentity.cpp \
        ../../src/lib/engine/rg_line.cpp \
        ../../src/lib/engine/rg_vector.cpp \
        ../../src/lib/engine/rg_painter.cpp \
        ../../src/lib/engine/rg_painterqt.cpp\
        ../../src/lib/gui/rg_coordinateevent.cpp \
        ../../src/lib/modification/rg_selection.cpp \
        ../../src/lib/engine/rg_pen.cpp \
        ../../src/lib/engine/rg_overlayrect.cpp \
        ../../src/lib/information/rg_information.cpp \
        ../../src/lib/geom/geom.cpp \
        ../../src/lib/engine/rg_marker.cpp \
        ../../src/lib/modification/rg_modification.cpp \
        ../../src/lib/engine/rg_undo.cpp \
        ../../src/lib/engine/rg_undogroup.cpp \
        ../../src/lib/engine/rg_rectangle.cpp \
        ../../src/lib/engine/rg_polygon.cpp \
    ../../src/actions/rg_actioneditaddvertex.cpp \
    ../../src/actions/rg_actioneditdelvertex.cpp \
    ../../src/ui/forms/ru_informationwidget.cpp

HEADERS += \
        ../../src/lib/debug/rl_debug.h \
        ../../src/lib/rl_settings.h \
        ../../src/lib/gui/rl_dialogfactoryinterface.h\
        ../../src/lib/gui/rl_dialogfactory.h \
        ../../src/lib/engine/rg_undoable.h \
        ../../src/lib/engine/rg_entity.h \
        ../../src/lib/engine/rg_entitycontainer.h \
        ../../src/lib/engine/rg_document.h \
        ../../src/lib/engine/rg_graphic.h \
        ../../src/lib/gui/rg_graphicview.h \
        ../../src/lib/actions/rg_snapper.h \
        ../../src/lib/actions/rg_actioninterface.h \
        ../../src/lib/actions/rg_previewactioninterface.h \
        ../../src/lib/actions/rg_preview.h \
        ../../src/lib/engine/rg.h \
        ../../src/lib/gui/rg_eventhandler.h \
        ../../src/lib/engine/rg_atomicentity.h \
        ../../src/lib/engine/rg_line.h \
        ../../src/lib/engine/rg_vector.h \
        ../../src/lib/engine/rg_painter.h \
        ../../src/lib/engine/rg_painterqt.h\
        ../../src/lib/gui/rg_coordinateevent.h \
        ../../src/lib/modification/rg_selection.h \
        ../../src/lib/engine/rg_pen.h \
        ../../src/lib/engine/rg_overlayrect.h \
        ../../src/lib/information/rg_information.h \
        ../../src/lib/geom/geom.h \
        ../../src/lib/engine/rg_marker.h \
        ../../src/lib/modification/rg_modification.h \
        ../../src/lib/engine/rg_undo.h \
        ../../src/lib/engine/rg_undogroup.h \
        ../../src/lib/engine/rg_rectangle.h \
        ../../src/lib/engine/rg_polygon.h \
        ../../src/actions/rg_actioneditaddvertex.h \
        ../../src/actions/rg_actioneditdelvertex.h \
        ../../src/ui/forms/ru_informationwidget.h


##################################################################
# User Interface

SOURCES += \
        ../../src/ui/rs_centralwidget.cpp \
        ../../src/ui/rs_actionfactory.cpp \
        ../../src/ui/rs_actionhandler.cpp \
        ../../src/ui/rs_actiongroupmanager.cpp \
        ../../src/ui/rs_widgetfactory.cpp \
        ../../src/ui/rs_dialogfactory.cpp \
        ../../src/ui/rs_graphicview.cpp \
        ../../src/ui/rs_scrollbar.cpp \
        ../../src/ui/forms/ru_coordinatewidget.cpp
HEADERS += \
        ../../src/ui/rs_centralwidget.h \
        ../../src/ui/rs_actionfactory.h \
        ../../src/ui/rs_actionhandler.h \
        ../../src/ui/rs_actiongroupmanager.h \
        ../../src/ui/rs_widgetfactory.h \
        ../../src/ui/rs_dialogfactory.h \
        ../../src/ui/rs_graphicview.h \
        ../../src/ui/rs_scrollbar.h \
        ../../src/ui/forms/ru_coordinatewidget.h


##################################################################
# main
SOURCES += \
#        ../../src/main/main.cpp \
        ../../src/main/rf_mainwindow.cpp \
        ../../src/main/ru_dialogfactory.cpp \
        ../../src/main/ru_mdiwindow.cpp

HEADERS += \
        ../../src/main/rf_mainwindow.h \
        ../../src/main/ru_dialogfactory.h \
        ../../src/main/ru_mdiwindow.h


##################################################################
# Actions

SOURCES += \
        ../../src/actions/rg_actiondrawline.cpp \
        ../../src/actions/rg_actiondefault.cpp \
        ../../src/actions/rg_actionzoom.cpp \
        ../../src/actions/rg_actionzoompan.cpp \
        ../../src/actions/rg_actionundo.cpp \
        ../../src/actions/rg_actiondrawrectangle.cpp \
        ../../src/actions/rg_actiondrawpolygon.cpp \
        ../../src/actions/rg_actioneditrotate.cpp \
        ../../src/actions/rg_actionselect.cpp
HEADERS += \
        ../../src/actions/rg_actiondrawline.h \
        ../../src/actions/rg_actiondefault.h \
        ../../src/actions/rg_actionzoom.h \
        ../../src/actions/rg_actionzoompan.h \
        ../../src/actions/rg_actionundo.h \
        ../../src/actions/rg_actiondrawrectangle.h \
        ../../src/actions/rg_actiondrawpolygon.h \
        ../../src/actions/rg_actioneditrotate.h \
        ../../src/actions/rg_actionselect.h

SOURCES += \
        tst_test_rg_entity.cpp

HEADERS +=
