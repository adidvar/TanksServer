TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        channel.cpp \
        game.cpp \
        main.cpp \
        server.cpp \
        player_controller.cpp \
        tank.cpp \
        vector2f.cpp

DISTFILES += \
    request_sketch

HEADERS += \
    archive.h \
    channel.h \
    game.h \
    out.h \
    player_controller.h \
    server.h \
    tank.h \
    vector2f.h

LIBS += -LD:/Libs/SFMLx32/lib/ -lsfml-system -lsfml-network

INCLUDEPATH += D:/Libs/SFMLx32/include
DEPENDPATH += D:/Libs/SFMLx32/include

win32: LIBS += -LD:/Libs/sfml-64/lib/ -lsfml-network-s

INCLUDEPATH += D:/Libs/sfml-64/include
DEPENDPATH += D:/Libs/sfml-64/include

win32:!win32-g++: PRE_TARGETDEPS += D:/Libs/sfml-64/lib/sfml-network-s.lib
else:win32-g++: PRE_TARGETDEPS += D:/Libs/sfml-64/lib/libsfml-network-s.a
