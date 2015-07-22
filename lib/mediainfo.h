#ifndef __MEDIAINFO_H__
#define __MEDIAINFO_H__
#include <stdio.h>

//#define DEBUG_OPEN

typedef struct MetaNameMapEntry
{
	int key;
	const char *tagName;
} MetaNameMapEntry;

enum {
	METADATA_KEY_DURATION				= 0,
	METADATA_KEY_START_TIME				= 1,
	METADATA_KEY_BITRATE				= 2,
	METADATA_KEY_HAS_AUDIO				= 3,
	METADATA_KEY_HAS_VIDEO				= 4,
	METADATA_KEY_FRAME_RATE				= 5,
	METADATA_KEY_TBN					= 6,
	METADATA_KEY_TBC					= 7,
	METADATA_KEY_PAR					= 8,
	METADATA_KEY_DAR					= 9,
	METADATA_KEY_VIDEO_CODEC			= 10,
	METADATA_KEY_AUDIO_CODEC			= 11,
	METADATA_KEY_TITLE					= 12,
	METADATA_KEY_ALBUM					= 13,
	METADATA_KEY_ARTIST					= 14,
	METADATA_KEY_GENRE					= 15,
	METADATA_KEY_ALBUMARTIST			= 16,
	METADATA_KEY_LANGUAGE				= 17,
	METADATA_KEY_CD_TRACK_NUMBER		= 18,
	METADATA_KEY_DATE					= 19,
	METADATA_KEY_TYER					= 20,
	METADATA_KEY_COMMENT				= 21,
	METADATA_KEY_TAGGING_TIME			= 22,
	METADATA_KEY_TOOL_NAME				= 23,
	METADATA_KEY_ENCODER				= 24,
	METADATA_KEY_YEAR					= 25,
	METADATA_KEY_COMPOSER				= 26,
	METADATA_KEY_ORGANIZATION			= 27,
	METADATA_KEY_AUTHOR					= 28,
	METADATA_KEY_COPYRIGHT				= 29,

	// Add more here...
};

MetaNameMapEntry MetaNameMap[] = {
	{METADATA_KEY_DURATION,				"Duration"},
	{METADATA_KEY_START_TIME,			"Start time"},
	{METADATA_KEY_BITRATE,				"Bitrate"},
	{METADATA_KEY_HAS_AUDIO,			"Has audio"},
	{METADATA_KEY_HAS_VIDEO,			"Has video"},
	{METADATA_KEY_FRAME_RATE,			"Framerate"},
	{METADATA_KEY_TBN,					"TBN"},
	{METADATA_KEY_TBC,					"TBC"},
	{METADATA_KEY_PAR,					"PAR"},
	{METADATA_KEY_DAR,					"DAR"},
	{METADATA_KEY_VIDEO_CODEC,			"Video"},
	{METADATA_KEY_AUDIO_CODEC,			"Audio"},
	{METADATA_KEY_TITLE,				"Title"},
	{METADATA_KEY_ALBUM,				"Album"},
	{METADATA_KEY_ARTIST,				"Artist"},
	{METADATA_KEY_GENRE,				"Genre"},
	{METADATA_KEY_ALBUMARTIST,			"Album_Artist"},
	{METADATA_KEY_LANGUAGE,				"Language"},
	{METADATA_KEY_CD_TRACK_NUMBER,		"Track"},
	{METADATA_KEY_DATE,					"Date"},
	{METADATA_KEY_TYER,					"Tyer"},
	{METADATA_KEY_COMMENT,				"Comment"},
	{METADATA_KEY_TAGGING_TIME,			"Tagging time"},
	{METADATA_KEY_TOOL_NAME,			"Tool name"},
	{METADATA_KEY_ENCODER,				"Encode"},
	{METADATA_KEY_YEAR,					"Year"},
	{METADATA_KEY_COMPOSER,				"Composer"},
	{METADATA_KEY_ORGANIZATION,			"Organization"},
	{METADATA_KEY_AUTHOR,				"Author"},
	{METADATA_KEY_COPYRIGHT,			"Copyright"},
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

const int MAX_METADATA_STRING_LENGTH = 512;
const int NUM_METADATA_KEYS = 30;

#define DIM(a) (sizeof(a)/ sizeof(a[0]))
char mMetadataValues[30][512];
#endif

void media_info (const char *filename, char msg[]);
void collect_meta (const char *filename);