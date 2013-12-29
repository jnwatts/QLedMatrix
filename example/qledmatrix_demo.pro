PROJECT                 = qledmatrix_demo
TARGET                  = qledmatrix_demo
TEMPLATE                = app

CONFIG                 += release

CONFIG                 += qt
CONFIG                 += warn_on

OBJECTS_DIR             = obj
MOC_DIR                 = moc
RCC_DIR                 = rcc

DEPENDPATH             += .
INCLUDEPATH            += ../
QMAKE_LIBDIR           += ../build

SOURCES                += main.cpp
RESOURCES              += qledmatrix_demo.qrc
LIBS                   += -lqledmatrix
