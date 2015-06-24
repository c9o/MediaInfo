
all:
	gcc gst-discoverer.c -o gst-discoverer `pkg-config --cflags --libs gstreamer-1.0 gstreamer-pbutils-1.0`

clean:
	rm -rf *.o gst-discoverer
