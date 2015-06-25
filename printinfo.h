
#ifndef __PRINTINFO_H__
#define __PRINTINFO_H__

#include <locale.h>
#include <stdlib.h>
#include <glib.h>
#include <gst/gst.h>
#include <gst/pbutils/pbutils.h>

gboolean async = FALSE;
gboolean show_toc = FALSE;
gboolean verbose = FALSE;

void gst_stream_information_to_string (GstDiscovererStreamInfo * info, GString * s, gint depth);
gchar *gst_stream_audio_information_to_string (GstDiscovererStreamInfo * info, gint depth);
gchar *gst_stream_video_information_to_string (GstDiscovererStreamInfo * info, gint depth);
gchar *gst_stream_subtitle_information_to_string (GstDiscovererStreamInfo * info, gint depth);
void print_stream_info (GstDiscovererStreamInfo * info, void *depth);
void print_topology (GstDiscovererStreamInfo * info, gint depth);
void print_tag_foreach (const GstTagList * tags, const gchar * tag, gpointer user_data);
void print_toc_entry (gpointer data, gpointer user_data);
void print_properties (GstDiscovererInfo * info, gint tab);
void print_info (GstDiscovererInfo * info, GError * err);

#endif
