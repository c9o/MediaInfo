#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/mathematics.h>
#include "mediainfo.h"

#ifdef DEBUG_OPEN
char msg[4096];
int offset;
#endif

static void print_fps(double d, const char *postfix)
{
	uint64_t v = lrintf(d * 100);
	if (v % 100)
	{
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, ", %3.2f %s", d, postfix);
#endif

		if (strcmp(postfix, "fps") == 0)
			snprintf (mMetadataValues[MetaNameMap[5].key], MAX_METADATA_STRING_LENGTH, "%3.2f %s", d, postfix);
		else
			snprintf (mMetadataValues[MetaNameMap[7].key], MAX_METADATA_STRING_LENGTH, "%3.2f %s", d, postfix);
	}
	else if (v % (100 * 1000))
	{
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, ", %1.0f %s", d, postfix);
#endif

		if (strcmp(postfix, "fps") == 0)
			snprintf (mMetadataValues[MetaNameMap[5].key], MAX_METADATA_STRING_LENGTH, "%1.0f %s", d, postfix);
		else
			snprintf (mMetadataValues[MetaNameMap[7].key], MAX_METADATA_STRING_LENGTH, "%1.0f %s", d, postfix);
	}
	else
	{
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, ", %1.0fk %s", d / 1000, postfix);
#endif

		snprintf (mMetadataValues[MetaNameMap[6].key], MAX_METADATA_STRING_LENGTH, "%1.0fk %s", d / 1000, postfix);
	}
}

static void dump_metadata(void *ctx, AVDictionary *m, const char *indent)
{
	int i = 0;

	if (m && !(av_dict_count(m) == 1 && av_dict_get(m, "language", NULL, 0))) {
		AVDictionaryEntry *tag = NULL;

#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "%sMetadata:\n", indent);

		while ((tag = av_dict_get(m, "", tag, AV_DICT_IGNORE_SUFFIX)))
			if (strcmp("language", tag->key))
			{
				offset += snprintf (msg+offset, sizeof(msg)-offset, "%s  %-8s: %s\n", indent, tag->key, tag->value);
			}
#endif

		for (i = 12; i < (int) DIM (MetaNameMap); i++) {
		tag = av_dict_get (m, MetaNameMap[i].tagName, NULL, AV_DICT_IGNORE_SUFFIX);

		if (tag) {
			snprintf (mMetadataValues[MetaNameMap[i].key], MAX_METADATA_STRING_LENGTH, "%s", tag->value);

#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, "%s  %-8s: %s\n", indent, tag->key, tag->value);
#endif
			}
		}
	}
}

/* "user interface" functions */
static void dump_stream_format(AVFormatContext *ic, int i, int index, int is_output)
{
	int flags = (is_output ? ic->oformat->flags : ic->iformat->flags);
	AVStream *st = ic->streams[i];
	AVDictionaryEntry *lang = av_dict_get(st->metadata, "language", NULL, 0);

	/* the pid is an important information, so we display it */
	/* XXX: add a generic system */
#ifdef DEBUG_OPEN
	if (flags & AVFMT_SHOW_IDS)
	{
		offset += snprintf (msg+offset, sizeof(msg)-offset, "[0x%x]", st->id);
	}
#endif

	if (lang)
	{
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "(%s)", lang->value);
#endif

		snprintf (mMetadataValues[MetaNameMap[17].key], MAX_METADATA_STRING_LENGTH, "(%s)", lang->value);
	}

	if (st->sample_aspect_ratio.num && av_cmp_q(st->sample_aspect_ratio, st->codec->sample_aspect_ratio)) {
		AVRational display_aspect_ratio;
		av_reduce(&display_aspect_ratio.num, &display_aspect_ratio.den,
				st->codec->width  * st->sample_aspect_ratio.num,
				st->codec->height * st->sample_aspect_ratio.den,
				1024 * 1024);

#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, ", PAR %d:%d DAR %d:%d", st->sample_aspect_ratio.num, st->sample_aspect_ratio.den, display_aspect_ratio.num, display_aspect_ratio.den);
#endif

		snprintf (mMetadataValues[MetaNameMap[8].key], MAX_METADATA_STRING_LENGTH, "PAR %d:%d", st->sample_aspect_ratio.num, st->sample_aspect_ratio.den);
		snprintf (mMetadataValues[MetaNameMap[9].key], MAX_METADATA_STRING_LENGTH, "DAR %d:%d", display_aspect_ratio.num, display_aspect_ratio.den);
	}

	if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
		if (st->avg_frame_rate.den && st->avg_frame_rate.num)
			print_fps(av_q2d(st->avg_frame_rate), "fps");
		if (st->time_base.den && st->time_base.num)
			print_fps(1 / av_q2d(st->time_base), "tbn");
		if (st->codec->time_base.den && st->codec->time_base.num)
			print_fps(1 / av_q2d(st->codec->time_base), "tbc");
	}

#ifdef DEBUG_OPEN
	offset += snprintf (msg+offset, sizeof(msg)-offset, "\n");
	//dump_metadata(NULL, st->metadata, "");
#endif
}

void dump_format(AVFormatContext *ic, int index, const char *url, int is_output)
{
	int i;
	uint8_t *printed = ic->nb_streams ? av_mallocz(ic->nb_streams) : NULL;
	if (ic->nb_streams && !printed)
		return;

#ifdef DEBUG_OPEN
	offset += snprintf (msg+offset, sizeof(msg)-offset, "%s '%s':\n",
			is_output ? "To" : "From", url);
#endif
	dump_metadata(NULL, ic->metadata, "  ");

	if (!is_output) {
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "Duration: ");
#endif

		if (ic->duration != AV_NOPTS_VALUE) {
			int hours, mins, secs, us;
			secs  = ic->duration / AV_TIME_BASE;
			us    = ic->duration % AV_TIME_BASE;
			mins  = secs / 60;
			secs %= 60;
			hours = mins / 60;
			mins %= 60;

#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, "%02d:%02d:%02d.%02d", hours, mins, secs, (100 * us) / AV_TIME_BASE);
#endif
			snprintf (mMetadataValues[MetaNameMap[0].key], MAX_METADATA_STRING_LENGTH, "%02d:%02d:%02d.%02d", hours, mins, secs, (100 * us) / AV_TIME_BASE);
		} else {
#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, "N/A");
#endif
			snprintf (mMetadataValues[MetaNameMap[0].key], MAX_METADATA_STRING_LENGTH, "N/A");
		}
		if (ic->start_time != AV_NOPTS_VALUE) {
			int hours, mins, secs, us;
#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, ", start: ");
#endif
			secs = ic->start_time / AV_TIME_BASE;
			us   = abs(ic->start_time % AV_TIME_BASE);
			mins  = secs / 60;
			secs %= 60;
			hours = mins / 60;
			mins %= 60;
#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, "%02d:%02d:%02d.%04d", hours, mins, secs, (int) av_rescale(us, 10000, AV_TIME_BASE));
#endif
			snprintf (mMetadataValues[MetaNameMap[1].key], MAX_METADATA_STRING_LENGTH, "%02d:%02d:%02d.%06d", hours, mins, secs, (int) av_rescale(us, 1000000, AV_TIME_BASE));
		}

#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, ", bitrate: ");
#endif

		if (ic->bit_rate)
		{
#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, "%d kb/s", ic->bit_rate / 1000);
#endif
			snprintf (mMetadataValues[MetaNameMap[2].key], MAX_METADATA_STRING_LENGTH, "%d kb/s", ic->bit_rate / 1000);
		}
		else
		{
#ifdef DEBUG_OPEN
			offset += snprintf (msg+offset, sizeof(msg)-offset, "N/A");
#endif
			snprintf (mMetadataValues[MetaNameMap[2].key], MAX_METADATA_STRING_LENGTH, "N/A");
		}

#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "\n");
#endif
	}

	int offset_v = 0;
	int offset_a = 0;
	for (i = 0; i < ic->nb_streams; i++)
	{
		AVStream *st = ic->streams[i];
		AVCodecContext *codec = st->codec;
		AVCodec *decoder = avcodec_find_decoder (codec->codec_id);
		int codec_type = codec->codec_type;
		char buf[256];

		avcodec_string(buf, sizeof(buf), st->codec, is_output);

#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "Stream #%d.%d", index, i);
		offset += snprintf (msg+offset, sizeof(msg)-offset, ": %s", buf);
#endif

		if (codec_type == AVMEDIA_TYPE_VIDEO) {
			snprintf (mMetadataValues[MetaNameMap[4].key], MAX_METADATA_STRING_LENGTH, "True");
			offset_v += snprintf (mMetadataValues[MetaNameMap[10].key] + offset_v, MAX_METADATA_STRING_LENGTH - offset_v, "\n%s", buf);
		} else if (codec_type == AVMEDIA_TYPE_AUDIO) {
			snprintf (mMetadataValues[MetaNameMap[3].key], MAX_METADATA_STRING_LENGTH, "True");
			offset_a += snprintf (mMetadataValues[MetaNameMap[11].key] + offset_a, MAX_METADATA_STRING_LENGTH - offset_a, "\n%s", buf);
		}

		if (!printed[i])
			dump_stream_format(ic, i, index, is_output);
	}

	av_free(printed);
}

int openFile (const char *url/*, AVFormatContext *format*/)
{
	int err = 0;
	AVFormatContext *fmt_ctx = NULL;
	AVInputFormat *iformat = NULL;
	AVDictionary *format_opts = NULL;
	AVDictionaryEntry *t = NULL;

	if ((err = avformat_open_input(&fmt_ctx, url, iformat, &format_opts)) < 0) {
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "err %d when opening %s\n", err, url);
#endif
		return err;
	}

	if ((t = av_dict_get(format_opts, "", NULL, AV_DICT_IGNORE_SUFFIX))) {
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "Option %s not found.\n", t->key);
#endif
		return AVERROR_OPTION_NOT_FOUND;
	}

	/* fill the streams in the format context */
	if ((err = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
#ifdef DEBUG_OPEN
		offset += snprintf (msg+offset, sizeof(msg)-offset, "err %d when finding stream info\n", err);
#endif
		return err;
	}

	dump_format(fmt_ctx, 0, url, 0);

	avformat_close_input(&fmt_ctx);

	return 0;
}

void media_info (const char *filename, char message[])
{
	int i = 0, off_msg = 0;

	message[0] = '\0';

	collect_meta (filename);

#if 0
	for (i = 0; i < (int) DIM (MetaNameMap); i++) {
	printf ("%-12s: %s \r\n", MetaNameMap[i].tagName, mMetadataValues[MetaNameMap[i].key]);
	}
#endif

#ifndef DEBUG_OPEN
	for (i = 0; i < (int) DIM (MetaNameMap); i++) {
		if (i < 6 || i == 10 || i == 11)
			off_msg += snprintf (message + off_msg, MAX_METADATA_STRING_LENGTH, "%-10s: %s \r\n", MetaNameMap[i].tagName, mMetadataValues[MetaNameMap[i].key]);
		else if (strcmp(mMetadataValues[MetaNameMap[i].key], "N/A"))
			off_msg += snprintf (message + off_msg, MAX_METADATA_STRING_LENGTH, "%-10s: %s \r\n", MetaNameMap[i].tagName, mMetadataValues[MetaNameMap[i].key]);
	}
#endif

	message[off_msg] = '\0';

#ifdef DEBUG_OPEN
	strncpy(message, msg, offset);
	message[offset] = '\0';
#endif

}

void collect_meta (const char *filename)
{
	printf ("filename is %s\n", filename);
	int i = 0;

	/* init libav */
	av_register_all ();
	avcodec_register_all ();

#ifdef DEBUG_OPEN
	offset = 0;
#endif

	/* init meta matrix */
	for (i = 0; i < (int) DIM (MetaNameMap); i++) {
		snprintf (mMetadataValues[MetaNameMap[i].key], MAX_METADATA_STRING_LENGTH, "N/A");
	}

	openFile (filename);

#ifdef DEBUG_OPEN
	offset += snprintf (msg+offset, sizeof(msg)-offset, "\n");
#endif
}
