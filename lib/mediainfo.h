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
	METADATA_KEY_START_TIME				,
	METADATA_KEY_BITRATE				,
	METADATA_KEY_MIMETYPE				,
	METADATA_KEY_HAS_VIDEO				,
	METADATA_KEY_HAS_AUDIO				,
	METADATA_KEY_VIDEO_CODEC			,
	METADATA_KEY_AUDIO_CODEC			,
	METADATA_KEY_VIDEO_PROFILE			,
	METADATA_KEY_AUDIO_PROFILE			,
	METADATA_KEY_AUDIO_SAMPLE_RATE		,
	METADATA_KEY_AUDIO_SAMPLE_FORMAT	,
	METADATA_KEY_FRAME_RATE				,
	METADATA_KEY_WIDTH					,
	METADATA_KEY_HEIGHT					,
	METADATA_KEY_TBN					,
	METADATA_KEY_TBC					,
	METADATA_KEY_PAR					,
	METADATA_KEY_DAR					,
	METADATA_KEY_TITLE					,
	METADATA_KEY_ALBUM					,
	METADATA_KEY_ARTIST					,
	METADATA_KEY_GENRE					,
	METADATA_KEY_ALBUMARTIST			,
	METADATA_KEY_LANGUAGE				,
	METADATA_KEY_CD_TRACK_NUMBER		,
	METADATA_KEY_DATE					,
	METADATA_KEY_TYER					,
	METADATA_KEY_COMMENT				,
	METADATA_KEY_TAGGING_TIME			,
	METADATA_KEY_TOOL_NAME				,
	METADATA_KEY_ENCODER				,
	METADATA_KEY_YEAR					,
	METADATA_KEY_COMPOSER				,
	METADATA_KEY_ORGANIZATION			,
	METADATA_KEY_AUTHOR					,
	METADATA_KEY_COPYRIGHT				= 36,

	// Add more here...
};

MetaNameMapEntry MetaNameMap[] = {
	{METADATA_KEY_DURATION,				"Duration"},
	{METADATA_KEY_START_TIME,			"Start Sime"},
	{METADATA_KEY_BITRATE,				"Bitrate"},
	{METADATA_KEY_MIMETYPE,				"Mime"},
	{METADATA_KEY_HAS_VIDEO,			"Has Video"},
	{METADATA_KEY_HAS_AUDIO,			"Has Audio"},
	{METADATA_KEY_VIDEO_CODEC,			"Video"},
	{METADATA_KEY_AUDIO_CODEC,			"Audio"},
	{METADATA_KEY_VIDEO_PROFILE,		"Video Profile"},
	{METADATA_KEY_AUDIO_PROFILE,		"Audio Profile"},
	{METADATA_KEY_AUDIO_SAMPLE_RATE,	"Sample Rate"},
	{METADATA_KEY_AUDIO_SAMPLE_FORMAT,	"Sample Format"},
	{METADATA_KEY_FRAME_RATE,			"Framerate"},
	{METADATA_KEY_WIDTH,				"Width"},
	{METADATA_KEY_HEIGHT,				"Height"},
	{METADATA_KEY_TBN,					"TBN"},
	{METADATA_KEY_TBC,					"TBC"},
	{METADATA_KEY_PAR,					"PAR"},
	{METADATA_KEY_DAR,					"DAR"},
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
	{METADATA_KEY_TAGGING_TIME,			"Tagging Time"},
	{METADATA_KEY_TOOL_NAME,			"Tool Name"},
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

const int MAX_METADATA_STRING_LENGTH = 128;
const int NUM_METADATA_KEYS = 37;

#define DIM(a) (sizeof(a)/ sizeof(a[0]))
char mMetadataValues[37][128];
#endif

void media_info (const char *filename, char msg[]);
void collect_meta (const char *filename);
