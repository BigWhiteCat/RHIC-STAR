INCLUDEPATH += $$system(include_star_files)

HEADERS += \
    StRoot/StV0Maker/StDcaService.h \
    StRoot/StV0Maker/StV0Dst.h \
    StRoot/StV0Maker/StV0Maker.h \
    StRoot/StV0Maker/StV0Type.h \
    StRoot/StV0Maker/QA.h \

SOURCES += \
    StRoot/StV0Maker/StDcaService.cxx \
    StRoot/StV0Maker/StV0Maker.cxx \
    Main.C \
    StRoot/StV0Maker/initQA.cpp
