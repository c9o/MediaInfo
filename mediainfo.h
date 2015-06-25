
#ifndef __MEDIAINFO_H__
#define __MEDIAINFO_H__

#include "printinfo.h"

/* *INDENT-OFF* */
void my_g_string_append_printf (GString * str, int depth, const gchar * format, ...) G_GNUC_PRINTF (3, 4);
/* *INDENT-ON* */

typedef struct {
  GstDiscoverer *dc;
  int argc;
  char **argv;
}PrivStruct;

void process_file (GstDiscoverer * dc, const gchar * filename);
void _new_discovered_uri (GstDiscoverer * dc, GstDiscovererInfo * info, GError * err);
gboolean _run_async (PrivStruct * ps);
void _discoverer_finished (GstDiscoverer * dc, GMainLoop * ml);

void
my_g_string_append_printf (GString * str, int depth, const gchar * format, ...)
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
