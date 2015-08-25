/****************************************************************************
**
** Copyright (c) [2015] Qualcomm Technologies International, Ltd.
** All Rights Reserved.
** Qualcomm Technologies Inc. Confidential and Proprietary.
** Not a Contribution. Notifications and licenses are retained for attribution
** purposes only . Your use of this code is governed by the terms of your
** license agreement with Qualcomm Technologies International, Ltd.(“QTIL”).
** Except as may be granted by separate express written agreement, this file
** provides no rights under or license to any QTIL or its affiliates patents,
** trademarks, copyrights,or other intellectual property.
**
****************************************************************************/

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
