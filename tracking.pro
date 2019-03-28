#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T12:59:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tracking
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv \
               /usr/local/include/opencv2

#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc \
#        -lopencv_objdetect -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_dnn \
#        -lraspicam_cv -lraspicam -lcurl
LIBS += -L/usr/local/lib/ -lopencv_aruco -lopencv_core -lopencv_imgproc \
        -lopencv_objdetect -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_dnn \
        -lcurl \
        /usr/local/lib/*.so


SOURCES += main.cpp\
        tracking.cpp

HEADERS  += tracking.h

FORMS    += tracking.ui
