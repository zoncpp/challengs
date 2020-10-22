
AM_CPPFLAGS = -std=c++11 -g -Wall -Wno-unknown-pragmas -Wno-deprecated-declarations
AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = ArvanProxy ArvanClient
 
ArvanProxy_SOURCES = ArvanProxy.cpp Common/Socket.cpp
ArvanClient_SOURCES = ArvanClient.cpp Common/Socket.cpp

ArvanProxy_LDADD = -lpthread
ArvanClient_LDADD = -lpthread

freeview_SOURCES = $(BUILT_SOURCES)
