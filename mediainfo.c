#include "mediainfo.h"
#include <stdio.h>

GstDiscovererInfo * process_file (GstDiscoverer * dc, const gchar * filename)
{
	GError *err = NULL;
	GDir *dir;
	gchar *uri, *path;
	GstDiscovererInfo *info;

	if (!gst_uri_is_valid (filename)) {
		/* Recurse into directories */
		if ((dir = g_dir_open (filename, 0, NULL))) {
			const gchar *entry;

			while ((entry = g_dir_read_name (dir))) {
				gchar *path;
				path = g_strconcat (filename, G_DIR_SEPARATOR_S, entry, NULL);
				info = process_file (dc, path);
				g_free (path);
			}

			g_dir_close (dir);
			return info;
		}

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

	//g_print ("Analyzing %s\n", uri);
	info = gst_discoverer_discover_uri (dc, uri, &err);
	if (err)
		g_error_free (err);

	g_free (uri);

	return info;
}

void media_info (const gchar * filename, gchar msg[])
{
	GError *err = NULL;
	GstDiscoverer *dc;
	GstDiscovererInfo *info;

	gst_init (NULL, NULL);

	dc = gst_discoverer_new (3 * GST_SECOND, &err);
	if (G_UNLIKELY (dc == NULL)) {
		g_print ("Error initializing: %s\n", err->message);
		sprintf (msg, "Error initializing: %s\n", err->message);
		exit (1);
	}

	info = process_file (dc, filename);
	print_info (info, err, msg);

	g_object_unref (dc);
	gst_discoverer_info_unref (info);
}
