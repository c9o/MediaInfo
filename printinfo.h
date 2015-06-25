#ifndef __PRINTINFO_H__
#define __PRINTINFO_H__

#include <locale.h>
#include <stdlib.h>
#include <glib.h>
#include <gst/gst.h>
#include <gst/pbutils/pbutils.h>

void print_tag_foreach (const GstTagList * tags, const gchar * tag, gpointer user_data);
void print_properties (GstDiscovererInfo * info, gint tab);
void print_info (GstDiscovererInfo * info, GError * err);

void my_g_string_append_printf (GString * str, int depth, const gchar * format, ...)
{
	va_list args;

	while (depth-- > 0) {
		g_string_append (str, "  ");
	}

	va_start (args, format);
	g_string_append_vprintf (str, format, args);
	va_end (args);
}

#endif
