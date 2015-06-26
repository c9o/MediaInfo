AUTOMAKE_OPTIONS=foreign
lib_LTLIBRARIES=libmediainfo.la
libmediainfo_la_SOURCES=mediainfo.c printinfo.c
libmediainfo_la_CFLAGS=`pkg-config --cflags --libs gstreamer-1.0 gstreamer-pbutils-1.0` -fPIC -shared -Xlinker -zmuldefs
include_HEADERS = mediainfo.h printinfo.h
