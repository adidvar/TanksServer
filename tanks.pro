TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bullet.cpp \
        container.cpp \
        debug_tools/collision_visualizer.cpp \
        game.cpp \
        main.cpp \
        map.cpp \
        math_tools/collision.cpp \
        math_tools/mvector.cpp \
        math_tools/shapes.cpp \
        module.cpp \
        net/channel.cpp \
        net/player_controller.cpp \
        net/server.cpp \
        objectinterface.cpp \
        playermodule.cpp \
        tank.cpp

DISTFILES += \
    request_sketch

HEADERS += \
    bullet.h \
    container.h \
    debug_tools/collision_visualizer.h \
    debug_tools/out.h \
    game.h \
    map.h \
    math_tools/collision.h \
    math_tools/mvector.h \
    math_tools/shapes.h \
    module.h \
    net/archive.h \
    net/channel.h \
    net/player_controller.h \
    net/server.h \
    object.h \
    objectinterface.h \
    playermodule.h \
    tank.h
	
CONFIG += conan_basic_setup
include(conanbuildinfo.pri)

win32:CONFIG(release, debug|release): LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network -lsfml-window -lsfml-graphics -lsfml-system -lws2_32
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network-d -lsfml-window-d -lsfml-graphics-d -lsfml-system-d -lws2_32
else:unix: LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network

INCLUDEPATH += D:/Libs/sfml-64/include
DEPENDPATH += D:/Libs/sfml-64/include
