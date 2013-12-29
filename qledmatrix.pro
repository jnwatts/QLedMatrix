PROJECT                 = qledmatrix
TARGET                  = qledmatrix
DESTDIR                 = build
TEMPLATE                = lib

CONFIG                 += debug_and_release

CONFIG                 += qt
CONFIG                 += warn_on
CONFIG                 += designer
CONFIG                 += plugin

DEFINES                += QT_NO_CAST_FROM_ASCII \
                          QT_NO_CAST_TO_ASCII \
                          QT_NO_KEYWORD

OBJECTS_DIR             = build/obj
MOC_DIR                 = build/moc
RCC_DIR                 = build/rcc
DEPENDDIR               = .
INCLUDEDIR              = .
HEADERS                += qledmatrix.h \
                          qledmatrixplugin.h
SOURCES                += qledmatrix.cpp \
                          qledmatrixplugin.cpp
RESOURCES              += qledmatrix.qrc

CONFIG(debug, debug|release) {
    mac:   TARGET       = qledmatrix_debug
    win32: TARGET       = qledmatrixd
}

unix:VERSION            = 0.6

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
