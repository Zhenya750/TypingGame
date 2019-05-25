include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
QT     += core widgets gui

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
QMAKE_CFLAGS += -Wall -Wextra -Werror

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov


HEADERS += \
    ../app/bullet.h \
    ../app/enemy.h \
    ../app/hero.h \
    ../app/mathfuncs.h \
    getrand_t.h \
    hero_recharge_t.h

SOURCES += \
    ../app/bullet.cpp \
    ../app/enemy.cpp \
    ../app/hero.cpp \
    main.cpp \
    ../app/mathfuncs.cpp

INCLUDEPATH += ../app

