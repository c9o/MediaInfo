#include <stdlib.h>
#include "mediainfo.h"

int main (int argc, char **argv)
{
	char msg[4096];

	if (argc < 2) {
		printf ("usage: %s <uris>\n", argv[0]);
		exit (-1);
	}

	media_info(argv[1], msg);

	printf ("%s", msg);

	return 0;
}
