TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    String.cpp \
    TweetRating.cpp \
    Tweet.cpp \
    WordExtraWeight.cpp \
    SentimentAnalyzer.cpp \
    test.cpp

HEADERS += \
    String.h \
    ArrayWrapper.h \
    Tweet.h \
    TweetRating.h \
    WordExtraWeight.h \
    SentimentAnalyzer.h \
    catch.hpp
