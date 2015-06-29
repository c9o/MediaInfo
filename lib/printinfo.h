#ifndef __PRINTINFO_H__
#define __PRINTINFO_H__

#include <locale.h>
#include <stdlib.h>
#include <glib.h>
#include <gst/gst.h>
#include <gst/pbutils/pbutils.h>

void print_tag_foreach (const GstTagList * tags, const gchar * tag, gpointer user_data);
void print_properties (GstDiscovererInfo * info, gint tab);
int print_info (GstDiscovererInfo * info, GError * err, gchar message[]);

#endif
