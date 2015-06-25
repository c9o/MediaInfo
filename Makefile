
all:
	gcc gst-discoverer.c -o gst-discoverer `pkg-config --cflags --libs gstreamer-1.0 gstreamer-pbutils-1.0`

clean:
	rm -rf *.o gst-discoverer testmediainfo libmediainfo.so

mediainfo:
	gcc -g -O2 printinfo.c mediainfo.c `pkg-config --cflags --libs gstreamer-1.0 gstreamer-pbutils-1.0` -fPIC -shared -o libmediainfo.so -Xlinker -zmuldefs

testmediainfo: mediainfo
	gcc -g -O2 testmediainfo.c -L. -lmediainfo `pkg-config --cflags --libs gstreamer-1.0 gstreamer-pbutils-1.0` -o testmediainfo
