QT += core quick widgets

CONFIG += c++17

SOURCES += \
        main.cpp \
        source/guiengine.cpp \
        source/models/blocks/addblocksmodel.cpp \
        source/models/blocks/blocksbasemodel.cpp \
        source/models/blocks/blocksmodel.cpp \
        source/models/blocks/calculationblock.cpp

RESOURCES += qml.qrc \
    resources.qrc

HEADERS += \
    source/guiengine.h \
    source/models/blocks/addblocksmodel.h \
    source/models/blocks/blocksbasemodel.h \
    source/models/blocks/blocksmodel.h \
    source/models/blocks/calculationblock.h
