#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T19:01:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osgEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QSCINTILLA_DLL

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qosgwidget.cpp \
    scenetreeitem.cpp \
    scenetreemodel.cpp \
    pickhandler.cpp \
    propertytreeitem.cpp \
    propertytreemodel.cpp \
    propertytreenodeitem.cpp \
    propertytreeobjectitem.cpp \
    propertytreeboundingsphereitem.cpp \
    propertytreestatesetitem.cpp \
    propertytreedelegate.cpp \
    propertytreemodelistitem.cpp \
    propertytreemodeitem.cpp \
    propertytreeattributelistitem.cpp \
    propertytreeattributeunknownitem.cpp \
    propertytreeattributeprogramitem.cpp \
    propertytreeattributeshaderitem.cpp \
    propertytreeattributeshadersourceitem.cpp \
    glsl/glsllexer.cpp \
    glsl/QsciLexerGlsl.cpp \
    qglsleditor.cpp \
    propertytreematrixtransformitem.cpp \
    propertytreeuniformlistitem.cpp \
    propertytreeuniformitem.cpp \
    propertytreenodemask.cpp

HEADERS += \
        mainwindow.h \
    qosgwidget.h \
    scenetreeitem.h \
    scenetreemodel.h \
    pickhandler.h \
    propertytreeitem.h \
    propertytreemodel.h \
    propertytreenodeitem.h \
    propertytreeobjectitem.h \
    propertytreepropertyitem.h \
    propertytreeboundingsphereitem.h \
    propertytreestatesetitem.h \
    propertytreedelegate.h \
    propertytreemodelistitem.h \
    propertytreemodeitem.h \
    propertytreeattributelistitem.h \
    propertytreeattributeunknownitem.h \
    propertytreeattributeprogramitem.h \
    propertytreeattributeshaderitem.h \
    propertytreeattributeshadersourceitem.h \
    glsl/FlexLexer.h \
    glsl/glsllexer.h \
    glsl/GlslLexer.lex \
    glsl/QsciLexerGlsl.h \
    qglsleditor.h \
    propertytreematrixtransformitem.h \
    propertytreeuniformlistitem.h \
    propertytreematrixitem.h \
    propertytreevectoritem.h \
    propertytreeuniformitem.h \
    propertytreebaseitem.h \
    propertytreeuniformunknownitem.h \
    propertytreenodemask.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += \
    ../QScintilla/include \
    ../OpenSceneGraph-3.4.1/include \
    ./glsl

LIBS += \
../QScintilla/lib/qscintilla2_qt5d.lib \
../OpenSceneGraph-3.4.1/lib/osgViewerd.lib \
../OpenSceneGraph-3.4.1/lib/osgGAd.lib \
../OpenSceneGraph-3.4.1/lib/osgDBd.lib \
../OpenSceneGraph-3.4.1/lib/osgUtild.lib \
../OpenSceneGraph-3.4.1/lib/osgFXd.lib \
../OpenSceneGraph-3.4.1/lib/osgd.lib \
../OpenSceneGraph-3.4.1/lib/osgTextd.lib \
../OpenSceneGraph-3.4.1/lib/osgManipulatord.lib \
../OpenSceneGraph-3.4.1/lib/OpenThreadsd.lib

DISTFILES += \
    glsl/README.txt
