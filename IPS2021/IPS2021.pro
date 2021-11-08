QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Tools/iconhelper.cpp \
    main.cpp \
    ips2021.cpp \
    src/camera.cpp \
    src/detector.cpp \
    src/global.cpp \
    src/maincontroller.cpp \
    src/message.cpp

HEADERS += \
    Tools/iconhelper.h \
    ips2021.h \
    src/camera.h \
    src/detector.h \
    src/global.h \
    src/maincontroller.h \
    src/message.h \
    src/myinclude.h

FORMS += \
    ips2021.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc

unix:!macx: LIBS += -L$$PWD/lib/opencv4.2.0/ -ljasper
unix:!macx: LIBS += -L$$PWD/lib/opencv4.2.0/ -lopencv_core
unix:!macx: LIBS += -L$$PWD/lib/opencv4.2.0/ -lopencv_imgcodecs
unix:!macx: LIBS += -L$$PWD/lib/opencv4.2.0/ -lopencv_imgproc
unix:!macx: LIBS += -L$$PWD/lib/modbus/ -lmodbus
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lMvCameraControl
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lFormatConversion
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lGCBase_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lGenApi_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/hik/ -llog4cpp_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lLog_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lMathParser_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lMediaProcess
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lMVGigEVisionSDK
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lMVRender
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lMvUsb3vTL
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lNodeMapData_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/hik/ -lXmlParser_gcc421_v3_0
unix:!macx: LIBS += -L$$PWD/lib/yaml-cpp/ -lyaml-cpp


INCLUDEPATH += $$PWD/include/opencv2
DEPENDPATH += $$PWD/include/opencv2

INCLUDEPATH += $$PWD/include/modbus
DEPENDPATH += $$PWD/include/modbus

INCLUDEPATH += $$PWD/include/hik/include
DEPENDPATH += $$PWD/include/hik/include

INCLUDEPATH += $$PWD/include/yaml-cpp
DEPENDPATH += $$PWD/include/yaml-cpp
