######################################################################
# Automatically generated by qmake (2.01a) mar may 6 21:10:56 2014
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . DB Model View
INCLUDEPATH += . View DB Model
QT += sql

# Input
HEADERS += DB/DBConnection.h \
           DB/QueryResult.h \
           Model/Book.h \
           Model/EntertainmentItem.h \
           Model/Error.h \
           Model/Loan.h \
           Model/LoanRequest.h \
           Model/Member.h \
           Model/Movie.h \
           Model/MusicAlbum.h \
           Model/OwnedItem.h \
           Model/Videogame.h \
           View/SELLoginDialog.h \
           View/SELMainLibraryWidget.h \
           View/SELMainWidget.h \
           View/SELMainWindow.h \
           View/SELUserAccountWidget.h \
           View/SELUserLibraryWidget.h \
           View/SELUserLoansWidget.h
SOURCES += main.cpp \
           DB/DBConnection.cpp \
           DB/QueryResult.cpp \
           Model/Book.cpp \
           Model/EntertainmentItem.cpp \
           Model/Error.cpp \
           Model/Loan.cpp \
           Model/LoanRequest.cpp \
           Model/Member.cpp \
           Model/Movie.cpp \
           Model/MusicAlbum.cpp \
           Model/OwnedItem.cpp \
           Model/Videogame.cpp \
           View/SELLoginDialog.cpp \
           View/SELMainLibraryWidget.cpp \
           View/SELMainWidget.cpp \
           View/SELMainWindow.cpp \
           View/SELUserAccountWidget.cpp \
           View/SELUserLibraryWidget.cpp \
           View/SELUserLoansWidget.cpp
