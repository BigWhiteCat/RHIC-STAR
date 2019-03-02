TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$system(include_star_files)

SOURCES += \
    StMyMaker.cxx

HEADERS += \
    StMyMaker.h
