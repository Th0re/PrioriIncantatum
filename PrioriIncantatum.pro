QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/cuboid.cpp \
    src/humanoid.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/cuboid.h \
    src/humanoid.h

RESOURCES += \
    ressources/shaders.qrc \

