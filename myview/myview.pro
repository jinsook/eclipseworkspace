TARGET = myview
QT += core \
    gui
CONFIG += uitools
HEADERS += qtgui/mainwindow.h \
    qtgui/ecanvas.h \
    geom/type.h \
    geom/painter.h \
    geom/rect.h
SOURCES += qtgui/mainwindow.cpp \
    geom/rect.cpp \
    main.cpp
FORMS += qtgui/mainwindow.ui
RESOURCES += 
TEMPLATE = app
