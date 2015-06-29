#include "mediainfo.h"
#include <stdio.h>

GstDiscovererInfo * process_file (GstDiscoverer * dc, const gchar * filename)
{
	GError *err = NULL;
	gchar *uri, *path;
	GstDiscovererInfo *info;

	if (!gst_uri_is_valid (filename)) {
		if (!g_path_is_absolute (filename)) {
			gchar *cur_dir;

			cur_dir = g_get_current_dir ();
			path = g_build_filename (cur_dir, filename, NULL);
			g_free (cur_dir);
		} else {
			path = g_strdup (filename);
		}

		uri = g_filename_to_uri (path, NULL, &err);
		g_free (path);
		path = NULL;

		if (err) {
			g_warning ("Couldn't convert filename to URI: %s\n", err->message);
			g_error_free (err);
			return NULL;
		}
	} else {
		uri = g_strdup (filename);
	}

	info = gst_discoverer_discover_uri (dc, uri, &err);
	if (err)
		g_error_free (err);

	g_free (uri);

	return info;
}

int media_info (const gchar * filename, gchar msg[])
{
	GError *err = NULL;
	GstDiscoverer *dc = NULL;
	GstDiscovererInfo *info = NULL;
	int ret = 0;

	gst_init (NULL, NULL);

	dc = gst_discoverer_new (3 * GST_SECOND, &err);
	if (G_UNLIKELY (dc == NULL)) {
		g_print ("Error initializing: %s\n", err->message);
		sprintf (msg, "Error initializing: %s\n", err->message);
		exit (1);
	}

	if (g_file_test (filename, G_FILE_TEST_IS_DIR))
	{
		g_warning ("Do not process dir");
		return 0;
	}

	if (g_file_test (filename, G_FILE_TEST_EXISTS))
	{
		info = process_file (dc, filename);
		ret = print_info (info, err, msg);
	}
	else
	{
		g_warning ("Not a valid filename");
		return 0;
	}

	g_object_unref (dc);
	gst_discoverer_info_unref (info);
	return ret;
}
