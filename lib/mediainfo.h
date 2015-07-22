#ifndef __MEDIAINFO_H__
#define __MEDIAINFO_H__
#include <stdio.h>

#if 1

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

	// Add more here...
};

MetaNameMapEntry MetaNameMap[] = {
	{METADATA_KEY_DURATION,				"duration"},
	{METADATA_KEY_START_TIME,			"start time"},
	{METADATA_KEY_BITRATE,				"bitrate"},
	{METADATA_KEY_HAS_AUDIO,			"has audio"},
	{METADATA_KEY_HAS_VIDEO,			"has video"},
	{METADATA_KEY_FRAME_RATE,			"framerate"},
	{METADATA_KEY_TBN,					"tbn"},
	{METADATA_KEY_TBC,					"tbc"},
	{METADATA_KEY_PAR,					"PAR"},
	{METADATA_KEY_DAR,					"DAR"},
	{METADATA_KEY_VIDEO_CODEC,			"video codec"},
	{METADATA_KEY_AUDIO_CODEC,			"audio codec"},
	{METADATA_KEY_TITLE,				"title"},
	{METADATA_KEY_ALBUM,				"album"},
	{METADATA_KEY_ARTIST,				"artist"},
	{METADATA_KEY_GENRE,				"genre"},
	{METADATA_KEY_ALBUMARTIST,			"album_artist"},
	{METADATA_KEY_LANGUAGE,				"language"},
	{METADATA_KEY_CD_TRACK_NUMBER,		"track"},
	{METADATA_KEY_DATE,					"date"},
	{METADATA_KEY_TYER,					"tyer"},
	{METADATA_KEY_COMMENT,				"comment"},
	{METADATA_KEY_TAGGING_TIME,			"tagging time"},
	{METADATA_KEY_TOOL_NAME,			"tool name"},
	{METADATA_KEY_ENCODER,				"encode"},
	{METADATA_KEY_YEAR,					"year"},
	{METADATA_KEY_COMPOSER,				"composer"},
	{METADATA_KEY_ORGANIZATION,			"organization"},
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
const int NUM_METADATA_KEYS = 28;

#define DIM(a) (sizeof(a)/ sizeof(a[0]))
char mMetadataValues[28][128];
#endif

void media_info (const char * filename, char msg[]);

#endif
