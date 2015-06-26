AUTOMAKE_OPTIONS=foreign
AM_CPPFLAGS= -I../lib
bin_PROGRAMS=testmediainfo
testmediainfo_SOURCES=testmediainfo.c
testmediainfo_LDADD=-lmediainfo -L../lib/
testmediainfo_CFLAGS=`pkg-config --cflags --libs gstreamer-1.0 gstreamer-pbutils-1.0`
