#include "mediainfo.h"

int main (int argc, char **argv)
{
	GError *err = NULL;
	GstDiscoverer *dc;
	GstDiscovererInfo *info;
	gchar msg[4096];

	if (argc < 2) {
		g_print ("usage: %s <uris>\n", argv[0]);
		exit (-1);
	}

	gst_init (NULL, NULL);

	dc = gst_discoverer_new (3 * GST_SECOND, &err);
	if (G_UNLIKELY (dc == NULL)) {
		g_print ("Error initializing: %s\n", err->message);
		exit (1);
	}

	info = process_file (dc, argv[1]);
	print_info (info, err, msg);

	g_print ("%s", msg);
	g_print ("\n");

	g_object_unref (dc);
	gst_discoverer_info_unref (info);

	return 0;
}
