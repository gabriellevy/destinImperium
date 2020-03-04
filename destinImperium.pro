#-------------------------------------------------
#
# Project created by QtCreator 2019-11-15T21:48:51
#
#-------------------------------------------------

QT       += core gui sql widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = destinImperium
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

include(factions/factions.pri)
include(types_planete/types_planete.pri)
include(socio_eco/socio_eco.pri)
include(actions/actions.pri)
include(warp/warp.pri)
include(humanite/humanite.pri)
include(texte/texte.pri)
include(techno/techno.pri)

CONFIG += c++11
CONFIG += resources_big

include(../destinLib/abs/abs.pri)
include(../destinLib/gen/gen.pri)
include(../destinLib/exec/exec.pri)

SOURCES += \
    ../destinLib/gestionnairecarac.cpp \
    ../destinLib/aspectratiolabel.cpp \
    ../destinLib/dbmanager.cpp \
    ../destinLib/glisseur.cpp \
    ../destinLib/reglages.cpp \
    ../destinLib/aleatoire.cpp \
    age.cpp \
    generateurnoeudsprobables.cpp \
    genviehumain.cpp \
    humain.cpp \
    imperium.cpp \
    main.cpp \
    metier.cpp

HEADERS += \
    ../destinLib/gestionnairecarac.h \
    ../destinLib/aspectratiolabel.h \
    ../destinLib/dbmanager.h \
    ../destinLib/glisseur.h \
    ../destinLib/reglages.h \
    ../destinLib/aleatoire.h \
    age.h \
    generateurnoeudsprobables.h \
    genviehumain.h \
    humain.h \
    imperium.h \
    metier.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES +=
