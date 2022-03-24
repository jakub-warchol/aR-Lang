QT += core quick widgets

CONFIG += c++17
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
        main.cpp \
        source/calculations/calculationengine.cpp \
        source/expression/expressiongenerator.cpp \
        source/guiengine.cpp \
        source/models/blocks/addblocksmodel.cpp \
        source/models/blocks/blocksbasemodel.cpp \
        source/models/blocks/blocksmodel.cpp \
        source/models/blocks/calculationblock.cpp \
        source/models/blocks/selectedblocksmodel.cpp \
        source/models/connection_lines/connectionlinesmodel.cpp \
        source/models/errors/errormodel.cpp

RESOURCES += qml.qrc \
    resources.qrc

HEADERS += \
    source/calculations/calculationengine.h \
    source/expression/expressiongenerator.h \
    source/guiengine.h \
    source/models/blocks/addblocksmodel.h \
    source/models/blocks/blocksbasemodel.h \
    source/models/blocks/blocksmodel.h \
    source/models/blocks/calculationblock.h \
    source/models/blocks/selectedblocksmodel.h \
    source/models/connection_lines/connectionlinesmodel.h \
    source/models/errors/errormodel.h
