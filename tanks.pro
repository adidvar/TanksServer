TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bullet.cpp \
        debug_tools/collision_visualizer.cpp \
        game.cpp \
        main.cpp \
        map.cpp \
        math_tools/collision.cpp \
        math_tools/mvector.cpp \
        math_tools/shapes.cpp \
        net/channel.cpp \
        net/player_controller.cpp \
        net/server.cpp \
        objectinterface.cpp \
        tank.cpp

DISTFILES += \
    request_sketch

HEADERS += \
    bullet.h \
    debug_tools/collision_visualizer.h \
    debug_tools/out.h \
    game.h \
    map.h \
    math_tools/collision.h \
    math_tools/mvector.h \
    math_tools/shapes.h \
    net/archive.h \
    net/channel.h \
    net/player_controller.h \
    net/server.h \
    object.h \
    objectinterface.h \
    tank.h

win32:CONFIG(release, debug|release): LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network -lsfml-window -lsfml-graphics -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network-d -lsfml-window-d -lsfml-graphics-d -lsfml-system-d
else:unix: LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network

INCLUDEPATH += D:/Libs/sfml-64/include
DEPENDPATH += D:/Libs/sfml-64/include
