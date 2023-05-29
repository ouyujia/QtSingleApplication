INCLUDEPATH	+= $$PWD
DEPENDPATH      += $$PWD
HEADERS		+= $$PWD/qtlocalpeer.h \
    $$PWD/qtsingleapplication.h
SOURCES		+= $$PWD/qtlocalpeer.cpp \
    $$PWD/qtsingleapplication.cpp

QT *= network

win32:contains(TEMPLATE, lib):contains(CONFIG, shared) {
    DEFINES += QT_QTSINGLECOREAPPLICATION_EXPORT=__declspec(dllexport)
}
