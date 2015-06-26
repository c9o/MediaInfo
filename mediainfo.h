#ifndef __MEDIAINFO_H__
#define __MEDIAINFO_H__

#include "printinfo.h"

typedef struct {
	GstDiscoverer *dc;
	int argc;
	char **argv;
}PrivStruct;

GstDiscovererInfo * process_file (GstDiscoverer * dc, const gchar * filename);
void media_info (const gchar * filename, gchar msg[]);

#endif
