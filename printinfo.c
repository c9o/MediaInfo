#include "printinfo.h"

void print_tag_foreach (const GstTagList * tags, const gchar * tag,
		gpointer user_data)
{
	GValue val = { 0, };
	gchar *str;
	gint depth = GPOINTER_TO_INT (user_data);

	gst_tag_list_copy_value (&val, tags, tag);

	if (G_VALUE_HOLDS_STRING (&val))
		str = g_value_dup_string (&val);
	else
		str = gst_value_serialize (&val);

	g_print ("%*s%s: %s\n", 2 * depth, " ", gst_tag_get_nick (tag), str);
	g_free (str);

	g_value_unset (&val);
}

void print_properties (GstDiscovererInfo * info, gint tab)
{
	const GstTagList *tags;

	g_print ("%*sDuration: %" GST_TIME_FORMAT "\n", tab + 1, " ",
			GST_TIME_ARGS (gst_discoverer_info_get_duration (info)));
	g_print ("%*sSeekable: %s\n", tab + 1, " ",
			(gst_discoverer_info_get_seekable (info) ? "yes" : "no"));
	if ((tags = gst_discoverer_info_get_tags (info))) {
		g_print ("%*sTags: \n", tab + 1, " ");
		gst_tag_list_foreach (tags, print_tag_foreach, GUINT_TO_POINTER (tab + 1));
	}
}

void print_info (GstDiscovererInfo * info, GError * err)
{
	GstDiscovererResult result = gst_discoverer_info_get_result (info);
	GstDiscovererStreamInfo *sinfo;

	g_print ("Done discovering %s\n", gst_discoverer_info_get_uri (info));
	switch (result) {
		case GST_DISCOVERER_OK:
			{
				break;
			}
		case GST_DISCOVERER_URI_INVALID:
			{
				g_print ("URI is not valid\n");
				break;
			}
		case GST_DISCOVERER_ERROR:
			{
				g_print ("An error was encountered while discovering the file\n");
				g_print (" %s\n", err->message);
				break;
			}
		case GST_DISCOVERER_TIMEOUT:
			{
				g_print ("Analyzing URI timed out\n");
				break;
			}
		case GST_DISCOVERER_BUSY:
			{
				g_print ("Discoverer was busy\n");
				break;
			}
		case GST_DISCOVERER_MISSING_PLUGINS:
			{
				g_print ("Missing plugins\n");
				break;
			}
	}

	if ((sinfo = gst_discoverer_info_get_stream_info (info))) {
		g_print ("\nProperties:\n");
		print_properties (info, 0);
		gst_discoverer_stream_info_unref (sinfo);
	}

	g_print ("\n");
}
