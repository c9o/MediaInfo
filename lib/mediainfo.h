#ifndef __MEDIAINFO_H__
#define __MEDIAINFO_H__
#include <stdio.h>
#if 0
/** album        -- name of the set this work belongs to
 * album_artist -- main creator of the set/album, if different from artist.
 *                 e.g. "Various Artists" for compilation albums.
 * artist       -- main creator of the work
 * comment      -- any additional description of the file.
 * composer     -- who composed the work, if different from artist.
 * copyright    -- name of copyright holder.
 * date         -- date when the work was created, preferably in ISO 8601.
 * disc         -- number of a subset, e.g. disc in a multi-disc collection.
 * encoder      -- name/settings of the software/hardware that produced the file.
 * encoded_by   -- person/group who created the file.
 * filename     -- original name of the file.
 * genre        -- <self-evident>.
 * language     -- main language in which the work is performed, preferably
 *                 in ISO 639-2 format.
 * performer    -- artist who performed the work, if different from artist.
 *                 E.g for "Also sprach Zarathustra", artist would be "Richard
 *                 Strauss" and performer "London Philharmonic Orchestra".
 * publisher    -- name of the label/publisher.
 * title        -- name of the work.
 * track        -- number of this work in the set, can be in form current/total.
 */
typedef struct MetaNameMapEntry
{
	int key;
	const char *tagName;
} MetaNameMapEntry;

// Keep these in synch with the constants defined in MediaMetadataRetriever.java
enum {
	METADATA_KEY_CD_TRACK_NUMBER 		= 0,
	METADATA_KEY_ALBUM           		= 1,
	METADATA_KEY_ARTIST          		= 2,
	METADATA_KEY_AUTHOR          		= 3,
	METADATA_KEY_COMPOSER        		= 4,
	METADATA_KEY_DATE            		= 5,
	METADATA_KEY_GENRE           		= 6,
	METADATA_KEY_TITLE           		= 7,
	METADATA_KEY_YEAR            		= 8,
	METADATA_KEY_DURATION        		= 9,
	METADATA_KEY_NUM_TRACKS      		= 10,
	METADATA_KEY_WRITER          		= 11,
	METADATA_KEY_MIMETYPE        		= 12,
	METADATA_KEY_ALBUMARTIST     		= 13,
	METADATA_KEY_DISC_NUMBER     		= 14,
	METADATA_KEY_COMPILATION     		= 15,
	METADATA_KEY_HAS_AUDIO       		= 16,
	METADATA_KEY_HAS_VIDEO       		= 17,
	METADATA_KEY_VIDEO_WIDTH     		= 18,
	METADATA_KEY_VIDEO_HEIGHT    		= 19,
	METADATA_KEY_BITRATE         		= 20,
	METADATA_KEY_TIMED_TEXT_LANGUAGES 	= 21,
	METADATA_KEY_IS_DRM          		= 22,
	METADATA_KEY_LOCATION        		= 23,
	METADATA_KEY_VIDEO_ROTATION  		= 24,
	METADATA_KEY_CODEC 			 		= 25,
	METADATA_KEY_RATING			 		= 26,
	METADATA_KEY_COMMENT		 		= 27,
	METADATA_KEY_COPYRIGHT		 		= 28,
	METADATA_KEY_FRAME_RATE		 		= 29,
	METADATA_KEY_VIDEO_FORMAT	 		= 30,

	// Add more here...
};

MetaNameMapEntry MetaNameMap[] = {
	{METADATA_KEY_CD_TRACK_NUMBER, 		"track"},
	{METADATA_KEY_ALBUM, 				"album"},
	{METADATA_KEY_ARTIST, 				"artist"},
	{METADATA_KEY_AUTHOR, 				"author"},
	{METADATA_KEY_COMPOSER, 			"composer"},
	{METADATA_KEY_DATE, 				"date"},
	{METADATA_KEY_GENRE, 				"genre"},
	{METADATA_KEY_TITLE, 				"title"},
	{METADATA_KEY_YEAR, 				"year"},
	{METADATA_KEY_DURATION, 			"duration"},
	{METADATA_KEY_NUM_TRACKS, 			"track count"},
	{METADATA_KEY_WRITER, 				"writer"},
	{METADATA_KEY_MIMETYPE, 			"mime type"},
	{METADATA_KEY_ALBUMARTIST, 			"album artist"},
	{METADATA_KEY_DISC_NUMBER, 			"disc"},
	{METADATA_KEY_COMPILATION, 			"compilation"},
	{METADATA_KEY_HAS_AUDIO, 			"has audio"},
	{METADATA_KEY_HAS_VIDEO, 			"has video"},
	{METADATA_KEY_VIDEO_WIDTH, 			"width"},
	{METADATA_KEY_VIDEO_HEIGHT, 		"height"},
	{METADATA_KEY_BITRATE,   			"bitrate"},
	{METADATA_KEY_TIMED_TEXT_LANGUAGES,	"language"},
	{METADATA_KEY_IS_DRM, 				"drm"},
	{METADATA_KEY_LOCATION, 			"location"},
	{METADATA_KEY_VIDEO_ROTATION, 		"rotation"},
	{METADATA_KEY_CODEC, 				"codec"},
	{METADATA_KEY_RATING,     			"rating"},
	{METADATA_KEY_COMMENT, 				"comment"},
	{METADATA_KEY_COPYRIGHT, 			"copyright"},
	{METADATA_KEY_FRAME_RATE, 			"framerate"},
	{METADATA_KEY_VIDEO_FORMAT, 		"videoformat"},
};

typedef struct MimeMapEntry
{
	const char *ffname;
	const char *mime;
} MimeMapEntry;

MimeMapEntry MimeMap[] = {
	{"mp3", "mpeg"},
	{"matroska", "x-matroska"},
	{"mov,mp4,m4a,3gp,3g2,mj2", "mp4"},
	{"mpeg", "mpeg"},
	{"avi", "avi"},
	{"ogg", "ogg"},
	{"rm", "rm"},
	{"ape", "ape"}
};

const int MAX_METADATA_STRING_LENGTH = 128;
const int NUM_METADATA_KEYS = 16;

#define DIM(a) (sizeof(a)/ sizeof(a[0]))
//char mMetadataValues[NUM_METADATA_KEYS][MAX_METADATA_STRING_LENGTH];
#endif

void media_info (const char * filename, char msg[]);

#endif
