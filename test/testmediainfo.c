#include "mediainfo.h"

int main (int argc, char **argv)
{
	gchar msg[4096];

	if (argc < 2) {
		g_print ("usage: %s <uris>\n", argv[0]);
		exit (-1);
	}

	media_info(argv[1], msg);

	g_print ("%s", msg);

	return 0;
}
