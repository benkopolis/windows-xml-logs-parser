# -------------------------------------------------
# Project created by QtCreator 2011-04-24T16:57:16
# -------------------------------------------------
QT += xml \
    xmlpatterns
QT -= gui
TARGET = WinXmlLogsParser
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    logparser.cpp \
    configuration.cpp \
    commons/exception.cpp \
    datafilter.cpp \
    eventsparsers/eventparser.cpp \
    eventsparsers/newprocesscreation.cpp \
    eventsparsers/processended.cpp \
    eventsparsers/userloggedin.cpp \
    event/event.cpp \
    eventsparsers/loginfailedeventparser.cpp \
    eventsparsers/userlogedouteventparser.cpp \
    event/loginfailedevent.cpp \
    event/newprocesscreationevent.cpp \
    event/processendedevent.cpp \
    event/userlogedinevent.cpp \
    event/userlogedoutevent.cpp \
    datamapper.cpp
HEADERS += logparser.h \
    configuration.h \
    commons/exception.h \
    datafilter.h \
    eventsparsers/eventparser.h \
    eventsparsers/newprocesscreation.h \
    eventsparsers/processended.h \
    eventsparsers/userloggedin.h \
    event/event.h \
    eventsparsers/loginfailedeventparser.h \
    eventsparsers/userlogedouteventparser.h \
    eventsparsers/parsers.h \
    event/loginfailedevent.h \
    event/newprocesscreationevent.h \
    event/processendedevent.h \
    event/userlogedinevent.h \
    event/userlogedoutevent.h \
    datamapper.h
