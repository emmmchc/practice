#-------------------------------------------------
#
# Project created by QtCreator 2019-01-31T13:26:58
#
#-------------------------------------------------

QT       += core gui sql
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test01
TEMPLATE = app
RC_ICONS = logo.ico


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    qdlglogin.cpp \
    mainwindow.cpp \
    usersmanage.cpp \
    person.cpp \
    classmanage.cpp \
    about.cpp \
    qwcomboboxdelegate.cpp \
    qwcheckboxdelegate.cpp \
    pjpyresult.cpp \
    regulation.cpp \
    cjimport.cpp \
    addscore.cpp \
    noeditdelegate.cpp \
    zwmanage.cpp \
    auditmanage.cpp \
    auditaddscore.cpp \
    excellenceapply.cpp \
    importrange.cpp \
    editpwd.cpp

HEADERS += \
    qdlglogin.h \
    mainwindow.h \
    usersmanage.h \
    person.h \
    classmanage.h \
    about.h \
    qwcomboboxdelegate.h \
    qwcheckboxdelegate.h \
    pjpyresult.h \
    regulation.h \
    cjimport.h \
    addscore.h \
    noeditdelegate.h \
    zwmanage.h \
    auditmanage.h \
    auditaddscore.h \
    excellenceapply.h \
    importrange.h \
    editpwd.h

FORMS += \
    qdlglogin.ui \
    mainwindow.ui \
    usersmanage.ui \
    person.ui \
    classmanage.ui \
    about.ui \
    pjpyresult.ui \
    regulation.ui \
    cjimport.ui \
    addscore.ui \
    zwmanage.ui \
    auditmanage.ui \
    auditaddscore.ui \
    excellenceapply.ui \
    importrange.ui \
    editpwd.ui
