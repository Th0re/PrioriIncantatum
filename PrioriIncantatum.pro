QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/cuboid.cpp \
    src/humanoid.cpp \
    src/particulefountain.cpp \
    src/lightninggenerator.cpp \
    src/cylinder.cpp \
    src/lightning.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/cuboid.h \
    src/humanoid.h \
    src/particulefountain.h \
    src/lightninggenerator.h \
    src/cylinder.h \
    src/lightning.h

RESOURCES += \
    ressources/shaders.qrc \

DISTFILES +=

