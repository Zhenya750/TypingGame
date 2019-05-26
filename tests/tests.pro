include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
QT     += core widgets gui

QMAKE_CXXFLAGS += -Wall -Wextra -Werror
QMAKE_CFLAGS += -Wall -Wextra -Werror
QMAKE_CXXFLAGS += -std=c++0x

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov


HEADERS += \
    ../app/bullet.h \
    ../app/enemy.h \
    ../app/hero.h \
    ../app/mathfuncs.h \
    ../app/vocabulary.h \
    enemy_docmp_t.h \
    enemy_heal_t.h \
    getrand_t.h \
    hero_isheadshot_t.h \
    hero_recharge_t.h \
    vocabulary_clearalpha_t.h \
    vocabulary_load_t.h

SOURCES += \
    ../app/bullet.cpp \
    ../app/enemy.cpp \
    ../app/hero.cpp \
    ../app/mathfuncs.cpp \
    ../app/vocabulary.cpp \
    main.cpp


INCLUDEPATH += ../app

RESOURCES += \
    files.qrc

