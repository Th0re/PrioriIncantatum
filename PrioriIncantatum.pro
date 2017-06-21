QT       += core gui widgets

TARGET = PrioriIncantatum
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/cuboid.cpp \
    src/humanoid.cpp \
    src/particulefountain.cpp \
    src/lightninggenerator.cpp \
    src/cylinder.cpp \
    src/lightning.cpp \
    src/floor.cpp


HEADERS += \
    src/mainwidget.h \
    src/cuboid.h \
    src/humanoid.h \
    src/particulefountain.h \
    src/lightninggenerator.h \
    src/cylinder.h \
    src/lightning.h \
    src/floor.h
RESOURCES += \
    ressources/shaders.qrc \

DISTFILES +=

