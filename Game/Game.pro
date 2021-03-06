TEMPLATE = app
TARGET = TheGame

QT += core gui widgets
QT += multimedia

CONFIG += c++14

SOURCES += \
    main.cpp \
    mapwindow.cc \
    startdialog.cpp \
    map.cpp \
    gameobjectmanager.cpp \
    gameeventhandler.cpp \
    player.cpp \
    Tiles/grasstile.cpp \
    gamemapgenerator.cpp \
    gametilebase.cpp \
    Tiles/foresttile.cpp \
    Tiles/watertile.cpp \
    Tiles/towntile.cpp \
    Buildings/farmbuilding.cpp \
    Buildings/loggingbuilding.cpp \
    Buildings/fishingbuilding.cpp \
    Workers/noviceworker.cpp \
    Workers/masterworker.cpp \
    gamebuildingbase.cpp \
    Workers/apprenticeworker.cpp \
    pricewindow.cpp \
    ruleswindow.cpp

HEADERS += \
    mapwindow.hh \
    startdialog.h \
    map.h \
    gameobjectmanager.h \
    gameeventhandler.h \
    player.h \
    Tiles/grasstile.h \
    gamemapgenerator.h \
    gametilebase.h \
    Tiles/foresttile.h \
    Tiles/watertile.h \
    Tiles/towntile.h \
    Buildings/farmbuilding.h \
    Buildings/loggingbuilding.h \
    Buildings/fishingbuilding.h \
    Workers/noviceworker.h \
    Workers/masterworker.h \
    gameresourcemap.h \
    gamebuildingbase.h \
    Workers/apprenticeworker.h \
    pricewindow.h \
    ruleswindow.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    startdialog.ui \
    pricewindow.ui \
    ruleswindow.ui
