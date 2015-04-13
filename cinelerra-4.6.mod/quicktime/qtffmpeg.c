#include "colormodels.h"
#include "funcprotos.h"
#include <pthread.h>
#include "quicktime.h"
#include "qtffmpeg.h"
#include "qtprivate.h"
#include <string.h>
// FFMPEG front end for quicktime.




// Different ffmpeg versions
#define FFMPEG_2010



int ffmpeg_initialized = 0;
pthread_mutex_t ffmpeg_lock = PTHREAD_MUTEX_INITIALIZER;




static void dump_context(void *ptr)
{
	AVCodecContext *context = (AVCodecContext*)ptr;

	printf("dump_context %d\n", __LINE__);
	printf("    log_level_offset=%d\n",context->log_level_offset);
	printf("    bit_rate=%d\n",context->bit_rate);
	printf("    bit_rate_tolerance=%d\n",context->bit_rate_tolerance);
	printf("    global_quality=%d\n",context->global_quality);
	printf("    compression_level=%d\n",context->compression_level);
	printf("    flags=%d\n",context->flags);
	printf("    flags2=%d\n",context->flags2);
	printf("    extradata_size=%d\n",context->extradata_size);
	printf("    ticks_per_frame=%d\n",context->ticks_per_frame);
	printf("    delay=%d\n",context->delay);
	printf("    width=%d\n",context->width);
	printf("    height=%d\n",context->height);
	printf("    coded_width=%d\n",context->coded_width);
	printf("    coded_height=%d\n",context->coded_height);
	printf("    gop_size=%d\n",context->gop_size);
	printf("    me_method=%d\n",context->me_method);
	printf("    max_b_frames=%d\n",context->max_b_frames);
	printf("    rc_strategy=%d\n",context->rc_strategy);
	printf("    b_frame_strategy=%d\n",context->b_frame_strategy);
	printf("    has_b_frames=%d\n",context->has_b_frames);
	printf("    mpeg_quant=%d\n",context->mpeg_quant);
	printf("    slice_count=%d\n",context->slice_count);
	printf("    prediction_method=%d\n",context->prediction_method);
	printf("    me_cmp=%d\n",context->me_cmp);
	printf("    me_sub_cmp=%d\n",context->me_sub_cmp);
	printf("    mb_cmp=%d\n",context->mb_cmp);
	printf("    ildct_cmp=%d\n",context->ildct_cmp);
	printf("    dia_size=%d\n",context->dia_size);
	printf("    last_predictor_count=%d\n",context->last_predictor_count);
	printf("    pre_me=%d\n",context->pre_me);
	printf("    me_pre_cmp=%d\n",context->me_pre_cmp);
	printf("    pre_dia_size=%d\n",context->pre_dia_size);
	printf("    me_subpel_quality=%d\n",context->me_subpel_quality);
	printf("    me_range=%d\n",context->me_range);
	printf("    intra_quant_bias=%d\n",context->intra_quant_bias);
	printf("    inter_quant_bias=%d\n",context->inter_quant_bias);
	printf("    slice_flags=%d\n",context->slice_flags);
	printf("    mb_decision=%d\n",context->mb_decision);
	printf("    scenechange_threshold=%d\n",context->scenechange_threshold);
	printf("    noise_reduction=%d\n",context->noise_reduction);
	printf("    intra_dc_precision=%d\n",context->intra_dc_precision);
	printf("    skip_top=%d\n",context->skip_top);
	printf("    skip_bottom=%d\n",context->skip_bottom);
	printf("    mb_lmin=%d\n",context->mb_lmin);
	printf("    mb_lmax=%d\n",context->mb_lmax);
	printf("    me_penalty_compensation=%d\n",context->me_penalty_compensation);
	printf("    bidir_refine=%d\n",context->bidir_refine);
	printf("    brd_scale=%d\n",context->brd_scale);
	printf("    keyint_min=%d\n",context->keyint_min);
	printf("    refs=%d\n",context->refs);
	printf("    chromaoffset=%d\n",context->chromaoffset);
	printf("    mv0_threshold=%d\n",context->mv0_threshold);
	printf("    b_sensitivity=%d\n",context->b_sensitivity);
	printf("    slices=%d\n",context->slices);
	printf("    sample_rate=%d\n",context->sample_rate);
	printf("    channels=%d\n",context->channels);
	printf("    frame_size=%d\n",context->frame_size);
	printf("    frame_number=%d\n",context->frame_number);
	printf("    block_align=%d\n",context->block_align);
	printf("    cutoff=%d\n",context->cutoff);
	printf("    refcounted_frames=%d\n",context->refcounted_frames);
	printf("    qmin=%d\n",context->qmin);
	printf("    qmax=%d\n",context->qmax);
	printf("    max_qdiff=%d\n",context->max_qdiff);
	printf("    rc_buffer_size=%d\n",context->rc_buffer_size);
	printf("    rc_override_count=%d\n",context->rc_override_count);
	printf("    rc_max_rate=%d\n",context->rc_max_rate);
	printf("    rc_min_rate=%d\n",context->rc_min_rate);
	printf("    rc_initial_buffer_occupancy=%d\n",context->rc_initial_buffer_occupancy);
	printf("    coder_type=%d\n",context->coder_type);
	printf("    context_model=%d\n",context->context_model);
	printf("    frame_skip_threshold=%d\n",context->frame_skip_threshold);
	printf("    frame_skip_factor=%d\n",context->frame_skip_factor);
	printf("    frame_skip_exp=%d\n",context->frame_skip_exp);
	printf("    frame_skip_cmp=%d\n",context->frame_skip_cmp);
	printf("    trellis=%d\n",context->trellis);
	printf("    min_prediction_order=%d\n",context->min_prediction_order);
	printf("    max_prediction_order=%d\n",context->max_prediction_order);
	printf("    timecode_frame_start=%jd\n",context->timecode_frame_start);
	printf("    rtp_payload_size=%d\n",context->rtp_payload_size);
	printf("    mv_bits=%d\n",context->mv_bits);
	printf("    header_bits=%d\n",context->header_bits);
	printf("    i_tex_bits=%d\n",context->i_tex_bits);
	printf("    p_tex_bits=%d\n",context->p_tex_bits);
	printf("    i_count=%d\n",context->i_count);
	printf("    p_count=%d\n",context->p_count);
	printf("    skip_count=%d\n",context->skip_count);
	printf("    misc_bits=%d\n",context->misc_bits);
	printf("    frame_bits=%d\n",context->frame_bits);
	printf("    workaround_bugs=%d\n",context->workaround_bugs);
	printf("    strict_std_compliance=%d\n",context->strict_std_compliance);
	printf("    error_concealment=%d\n",context->error_concealment);
	printf("    debug=%d\n",context->debug);
	printf("    debug_mv=%d\n",context->debug_mv);
	printf("    err_recognition=%d\n",context->err_recognition);
	printf("    reordered_opaque=%jd\n",context->reordered_opaque);
	printf("    dct_algo=%d\n",context->dct_algo);
	printf("    idct_algo=%d\n",context->idct_algo);
	printf("    bits_per_coded_sample=%d\n",context->bits_per_coded_sample);
	printf("    bits_per_raw_sample=%d\n",context->bits_per_raw_sample);
	printf("    lowres=%d\n",context->lowres);
	printf("    thread_count=%d\n",context->thread_count);
	printf("    thread_type=%d\n",context->thread_type);
	printf("    active_thread_type=%d\n",context->active_thread_type);
	printf("    thread_safe_callbacks=%d\n",context->thread_safe_callbacks);
	printf("    nsse_weight=%d\n",context->nsse_weight);
	printf("    profile=%d\n",context->profile);
	printf("    level=%d\n",context->level);
	printf("    subtitle_header_size=%d\n",context->subtitle_header_size);
	printf("    side_data_only_packets=%d\n",context->side_data_only_packets);
	printf("    initial_padding=%d\n",context->initial_padding);
	printf("    pts_correction_num_faulty_pts=%jd\n",context->pts_correction_num_faulty_pts);
	printf("    pts_correction_num_faulty_dts=%jd\n",context->pts_correction_num_faulty_dts);
	printf("    pts_correction_last_pts=%jd\n",context->pts_correction_last_pts);
	printf("    pts_correction_last_dts=%jd\n",context->pts_correction_last_dts);
	printf("    sub_charenc_mode=%d\n",context->sub_charenc_mode);
	printf("    skip_alpha=%d\n",context->skip_alpha);
	printf("    seek_preroll=%d\n",context->seek_preroll);
}

quicktime_ffmpeg_t* quicktime_new_ffmpeg(int cpus,
	int fields,
	int ffmpeg_id,
	int w,
	int h,
	quicktime_stsd_table_t *stsd_table)
{
	quicktime_ffmpeg_t *ptr = calloc(1, sizeof(quicktime_ffmpeg_t));
	quicktime_esds_t *esds = &stsd_table->esds;
	quicktime_avcc_t *avcc = &stsd_table->avcc;
	int i;

	ptr->fields = fields;
	ptr->width = w;
	ptr->height = h;
	ptr->ffmpeg_id = ffmpeg_id;


//printf("quicktime_new_ffmpeg 1 ffmpeg_id=%d\n", ptr->ffmpeg_id);
	if(ffmpeg_id == CODEC_ID_SVQ1)
	{
		ptr->width_i = quicktime_quantize32(ptr->width);
		ptr->height_i = quicktime_quantize32(ptr->height);
	}
	else
	{
		ptr->width_i = quicktime_quantize16(ptr->width);
		ptr->height_i = quicktime_quantize16(ptr->height);
	}

	pthread_mutex_lock(&ffmpeg_lock);
	if(!ffmpeg_initialized)
	{
		ffmpeg_initialized = 1;
		av_register_all();
	}

	for(i = 0; i < fields; i++)
	{
		ptr->decoder[i] = avcodec_find_decoder(ptr->ffmpeg_id);
		if(!ptr->decoder[i])
		{
			printf("quicktime_new_ffmpeg: avcodec_find_decoder returned NULL.\n");
			quicktime_delete_ffmpeg(ptr);
			return 0;
		}

		AVCodecContext *context = avcodec_alloc_context3(ptr->decoder[i]);
		ptr->decoder_context[i] = context;
		static char fake_data[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// 		static unsigned char extra_data[] =
// 		{
// 			0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20, 0x00, 0xc8, 0x88, 0xba, 0x98, 0x60, 0xfa, 0x67, 0x80, 0x91, 0x02, 0x83, 0x1f
// 		};
		context->width = ptr->width_i;
		context->height = ptr->height_i;
//		context->width = w;
//		context->height = h;
		context->extradata = fake_data;
		context->extradata_size = 0;

		if(esds->mpeg4_header && esds->mpeg4_header_size)
		{
			context->extradata = esds->mpeg4_header;
			context->extradata_size = esds->mpeg4_header_size;
		}

		if(avcc->data && avcc->data_size)
		{
			context->extradata = avcc->data;
			context->extradata_size = avcc->data_size;
		}
		if(cpus > 1)
		{
//			avcodec_thread_init(context, cpus);
			context->thread_count = cpus;
		}

		if(avcodec_open2(context, ptr->decoder[i], 0) < 0)
		{
			int error = 1;
// Try again with 1 thread
			if(cpus > 1)
			{
//				avcodec_thread_init(context, 1);
				context->thread_count = cpus;
				if(avcodec_open2(context, ptr->decoder[i], 0) >= 0)
				{
					error = 0;
				}
			}

			if(error)
			{
				printf("quicktime_new_ffmpeg: avcodec_open failed.\n");
				quicktime_delete_ffmpeg(ptr);
				ptr = NULL;
				break;
			}
		}



		ptr->last_frame[i] = -1;
	}
	pthread_mutex_unlock(&ffmpeg_lock);

	return ptr;
}



void quicktime_delete_ffmpeg(quicktime_ffmpeg_t *ptr)
{
	int i;
	if(ptr)
	{
		pthread_mutex_lock(&ffmpeg_lock);
		for(i = 0; i < ptr->fields; i++)
		{
			if(ptr->decoder_context[i])
			{
	    		avcodec_close(ptr->decoder_context[i]);
				free(ptr->decoder_context[i]);
			}
		}
		pthread_mutex_unlock(&ffmpeg_lock);



		if(ptr->temp_frame) free(ptr->temp_frame);
		if(ptr->work_buffer) free(ptr->work_buffer);


		free(ptr);
	}
}


//avcodec_get_frame_defaults
static void frame_defaults(AVFrame *frame)
{
	memset(frame, 0, sizeof(AVFrame));
	av_frame_unref(frame);
}



static int decode_wrapper(quicktime_t *file,
	quicktime_video_map_t *vtrack,
	quicktime_ffmpeg_t *ffmpeg,
	int frame_number,
	int current_field,
	int track,
	int drop_it)
{
	int got_picture = 0;
	int result = 0;
	int bytes = 0;
	int header_bytes = 0;
 	char *compressor = vtrack->track->mdia.minf.stbl.stsd.table[0].format;
	quicktime_trak_t *trak = vtrack->track;
	quicktime_stsd_table_t *stsd_table = &trak->mdia.minf.stbl.stsd.table[0];

// printf("decode_wrapper frame_number=%d current_field=%d drop_it=%d\n",
// frame_number,
// current_field,
// drop_it);

	quicktime_set_video_position(file, frame_number, track);

	bytes = quicktime_frame_size(file, frame_number, track);
	if(frame_number == 0)
	{
		header_bytes = stsd_table->esds.mpeg4_header_size;
	}

	if(!ffmpeg->work_buffer || ffmpeg->buffer_size < bytes + header_bytes)
	{
		if(ffmpeg->work_buffer) free(ffmpeg->work_buffer);
		ffmpeg->buffer_size = bytes + header_bytes;
		ffmpeg->work_buffer = calloc(1, ffmpeg->buffer_size + 100);
	}

	if(header_bytes)
		memcpy(ffmpeg->work_buffer, stsd_table->esds.mpeg4_header, header_bytes);

//printf("decode_wrapper %d frame_number=%d field=%d offset=0x%llx bytes=%d header_bytes=%d\n",
//__LINE__, frame_number, current_field, quicktime_ftell(file), bytes, header_bytes);
	if(!quicktime_read_data(file,
		ffmpeg->work_buffer + header_bytes,
		bytes))
		result = -1;

// static FILE *out = 0;
// if(!out) out = fopen("/tmp/debug.m2v", "w");
// fwrite(ffmpeg->work_buffer, bytes + header_bytes, 1, out);


	if(!result)
	{


// No way to determine if there was an error based on nonzero status.
// Need to test row pointers to determine if an error occurred.
		if(drop_it)
			ffmpeg->decoder_context[current_field]->skip_frame = AVDISCARD_NONREF /* AVDISCARD_BIDIR */;
		else
			ffmpeg->decoder_context[current_field]->skip_frame = AVDISCARD_DEFAULT;
		frame_defaults(&ffmpeg->picture[current_field]);

/*
 * printf("decode_wrapper %d frame_number=%d decoder_context=%p picture=%p buffer=%p bytes=%d\n",
 * __LINE__,
 * frame_number,
 * ffmpeg->decoder_context[current_field],
 * &ffmpeg->picture[current_field],
 * ffmpeg->work_buffer,
 * bytes + header_bytes);
 */


/*
 * if(frame_number >= 200 && frame_number < 280)
 * {
 * char string[1024];
 * sprintf(string, "/tmp/debug%03d", frame_number);
 * FILE *out = fopen(string, "w");
 * fwrite(ffmpeg->work_buffer, bytes, 1, out);
 * fclose(out);
 * }
 */


/*
 * dump_context(ffmpeg->decoder_context[current_field]);
 * ffmpeg->decoder_context[current_field]->bit_rate = 64000;
 * ffmpeg->decoder_context[current_field]->bit_rate_tolerance = 4000000;
 * ffmpeg->decoder_context[current_field]->codec_tag = 1482049860;
 */

		ffmpeg->decoder_context[current_field]->workaround_bugs =  FF_BUG_NO_PADDING;

// For ffmpeg.080508 you must add
// s->workaround_bugs =  FF_BUG_NO_PADDING;
// in h263dec.c to get MPEG-4 to work.
// Also must compile using -O2 instead of -O3 on gcc 4.1

#if LIBAVCODEC_VERSION_MAJOR < 53
		result = avcodec_decode_video(ffmpeg->decoder_context[current_field],
			&ffmpeg->picture[current_field], &got_picture,
			ffmpeg->work_buffer, bytes + header_bytes);
#else
{		AVPacket avpkt;
		av_init_packet(&avpkt);
		avpkt.data = ffmpeg->work_buffer;
		avpkt.size = bytes + header_bytes;
		avpkt.flags = AV_PKT_FLAG_KEY;
		result = avcodec_decode_video2(ffmpeg->decoder_context[current_field],
			&ffmpeg->picture[current_field], &got_picture, &avpkt);
}
#endif
		if(ffmpeg->picture[current_field].data[0])
		{
			result = 0;
		}
		else
		{
// ffmpeg can't recover if the first frame errored out, like in a direct copy
// sequence.
			result = 1;
		}
//printf("decode_wrapper %d %d result=%d\n", __LINE__, frame_number, result);

#ifdef ARCH_X86
		asm("emms");
#endif
	}

	return result;
}

// Get amount chroma planes are downsampled from luma plane.
// Used for copying planes into cache.
static int get_chroma_factor(quicktime_ffmpeg_t *ffmpeg, int current_field)
{
	switch(ffmpeg->decoder_context[current_field]->pix_fmt)
	{
		case PIX_FMT_YUV420P:
			return 4;
			break;
		case PIX_FMT_YUVJ420P:
			return 4;
			break;

#ifndef FFMPEG_2010
		case PIX_FMT_YUV422:
			return 2;
			break;
#endif

		case PIX_FMT_YUV422P:
			return 2;
			break;
		case PIX_FMT_YUV410P:
			return 9;
			break;
		default:
			fprintf(stderr,
				"get_chroma_factor: unrecognized color model %d\n",
				ffmpeg->decoder_context[current_field]->pix_fmt);
			return 9;
			break;
	}
}

int quicktime_ffmpeg_decode(quicktime_ffmpeg_t *ffmpeg,
	quicktime_t *file,
	unsigned char **row_pointers,
	int track)
{
	quicktime_video_map_t *vtrack = &(file->vtracks[track]);
	quicktime_trak_t *trak = vtrack->track;
	int current_field = vtrack->current_position % ffmpeg->fields;
	int input_cmodel;
	int result = 0;
	int seeking_done = 0;
	int i;

// Try frame cache
	result = quicktime_get_frame(vtrack->frame_cache,
		vtrack->current_position,
		&ffmpeg->picture[current_field].data[0],
		&ffmpeg->picture[current_field].data[1],
		&ffmpeg->picture[current_field].data[2]);


// Didn't get frame
	if(!result)
	{
// Codecs which work without locking:
// H264
// MPEG-4
//		pthread_mutex_lock(&ffmpeg_lock);

//printf("quicktime_ffmpeg_decode 1 %d\n", ffmpeg->last_frame[current_field]);

		if(ffmpeg->last_frame[current_field] == -1 &&
			ffmpeg->ffmpeg_id != CODEC_ID_H264)
		{
			int current_frame = vtrack->current_position;
// For certain codecs,
// must decode frame with stream header first but only the first frame in the
// field sequence has a stream header.
			result = decode_wrapper(file,
				vtrack,
				ffmpeg,
				current_field,
				current_field,
				track,
				0);
// Reset position because decode wrapper set it
			quicktime_set_video_position(file, current_frame, track);
			ffmpeg->last_frame[current_field] = current_field;
		}


// Handle seeking
// Seeking requires keyframes
		if(quicktime_has_keyframes(file, track) &&
// Not next frame
			vtrack->current_position != ffmpeg->last_frame[current_field] + ffmpeg->fields &&
// Same frame requested twice
			vtrack->current_position != ffmpeg->last_frame[current_field])
		{
			int frame1;
			int first_frame;
			int frame2 = vtrack->current_position;
			int current_frame = frame2;
			int do_i_frame = 1;

// If an interleaved codec, the opposite field would have been decoded in the previous
// seek.
			if(!quicktime_has_frame(vtrack->frame_cache, vtrack->current_position + 1))
				quicktime_reset_cache(vtrack->frame_cache);

// Get first keyframe of same field
			frame1 = current_frame;
			do
			{
				frame1 = quicktime_get_keyframe_before(file,
					frame1 - 1,
					track);
			}while(frame1 > 0 && (frame1 % ffmpeg->fields) != current_field);
//printf("quicktime_ffmpeg_decode 1 %d\n", frame1);

// For MPEG-4, get another keyframe before first keyframe.
// The Sanyo tends to glitch with only 1 keyframe.
// Not enough memory.
			if( 0 /* frame1 > 0 && ffmpeg->ffmpeg_id == CODEC_ID_MPEG4 */)
			{
				do
				{
					frame1 = quicktime_get_keyframe_before(file,
						frame1 - 1,
						track);
				}while(frame1 > 0 && (frame1 & ffmpeg->fields) != current_field);
//printf("quicktime_ffmpeg_decode 2 %d\n", frame1);
			}

// Keyframe is before last decoded frame and current frame is after last decoded
// frame, so instead of rerendering from the last keyframe we can rerender from
// the last decoded frame.
			if(frame1 < ffmpeg->last_frame[current_field] &&
				frame2 > ffmpeg->last_frame[current_field])
			{
				frame1 = ffmpeg->last_frame[current_field] + ffmpeg->fields;
				do_i_frame = 0;
			}

			first_frame = frame1;

/*
 * printf("quicktime_ffmpeg_decode 2 last_frame=%d frame1=%d frame2=%d\n",
 * ffmpeg->last_frame[current_field],
 * frame1,
 * frame2);
 */
			while(frame1 <= frame2)
			{
//printf("quicktime_ffmpeg_decode %d frame1=%d\n", __LINE__, frame1);
				result = decode_wrapper(file,
					vtrack,
					ffmpeg,
					frame1,
					current_field,
					track,
// Don't drop if we want to cache it
					0 /* (frame1 < frame2) */);

				if(ffmpeg->picture[current_field].data[0] &&
// FFmpeg seems to glitch out if we include the first frame.
					frame1 > first_frame)
				{
					int y_size = ffmpeg->picture[current_field].linesize[0] * ffmpeg->height_i;
					int u_size = y_size / get_chroma_factor(ffmpeg, current_field);
					int v_size = y_size / get_chroma_factor(ffmpeg, current_field);
					quicktime_put_frame(vtrack->frame_cache,
						frame1,
						ffmpeg->picture[current_field].data[0],
						ffmpeg->picture[current_field].data[1],
						ffmpeg->picture[current_field].data[2],
						y_size,
						u_size,
						v_size);
				}

// For some codecs,
// may need to do the same frame twice if it is the first I frame.
// 				if(do_i_frame)
// 				{
// printf("quicktime_ffmpeg_decode %d\n", __LINE__);
// 					result = decode_wrapper(file,
// 						vtrack,
// 						ffmpeg,
// 						frame1,
// 						current_field,
// 						track,
// 						0);
// 					do_i_frame = 0;
// 				}
				frame1 += ffmpeg->fields;
			}

			vtrack->current_position = frame2;
			seeking_done = 1;
		}

// Not decoded in seeking process
		if(!seeking_done &&
// Same frame not requested
			vtrack->current_position != ffmpeg->last_frame[current_field])
		{
//printf("quicktime_ffmpeg_decode %d\n", __LINE__);
			result = decode_wrapper(file,
				vtrack,
				ffmpeg,
				vtrack->current_position,
				current_field,
				track,
				0);
		}

//		pthread_mutex_unlock(&ffmpeg_lock);


		ffmpeg->last_frame[current_field] = vtrack->current_position;
	}

// Hopefully this setting will be left over if the cache was used.
	switch(ffmpeg->decoder_context[current_field]->pix_fmt)
	{
		case PIX_FMT_YUV420P:
			input_cmodel = BC_YUV420P;
			break;
#ifndef FFMPEG_2010
		case PIX_FMT_YUY422:
#endif
		case PIX_FMT_YUYV422:
			input_cmodel = BC_YUV422;
			break;

// It's not much of a decoder library
		case PIX_FMT_YUVJ420P:
			input_cmodel = BC_YUV420P;
			break;

		case PIX_FMT_YUV422P:
			input_cmodel = BC_YUV422P;
			break;
		case PIX_FMT_YUV410P:
			input_cmodel = BC_YUV9P;
			break;
		default:
			fprintf(stderr,
				"quicktime_ffmpeg_decode: unrecognized color model %d\n",
				ffmpeg->decoder_context[current_field]->pix_fmt);
			input_cmodel = 0;
			break;
	}

// printf("quicktime_ffmpeg_decode %d %lld ptr=%p\n",
// __LINE__,
// vtrack->current_position,
// ffmpeg->picture[current_field].data[0]);
	if(ffmpeg->picture[current_field].data[0])
	{
		unsigned char **input_rows;

		input_rows =
			malloc(sizeof(unsigned char*) *
			ffmpeg->decoder_context[current_field]->height);


		for(i = 0; i < ffmpeg->decoder_context[current_field]->height; i++)
			input_rows[i] = ffmpeg->picture[current_field].data[0] +
				i *
				ffmpeg->decoder_context[current_field]->width *
				cmodel_calculate_pixelsize(input_cmodel);


		cmodel_transfer(row_pointers, /* Leave NULL if non existent */
			input_rows,
			row_pointers[0], /* Leave NULL if non existent */
			row_pointers[1],
			row_pointers[2],
			ffmpeg->picture[current_field].data[0], /* Leave NULL if non existent */
			ffmpeg->picture[current_field].data[1],
			ffmpeg->picture[current_field].data[2],
			file->in_x,        /* Dimensions to capture from input frame */
			file->in_y,
			file->in_w,
			file->in_h,
			0,       /* Dimensions to project on output frame */
			0,
			file->out_w,
			file->out_h,
			input_cmodel,
			file->color_model,
			0,         /* When transfering BC_RGBA8888 to non-alpha this is the background color in 0xRRGGBB hex */
			ffmpeg->picture[current_field].linesize[0],       /* For planar use the luma rowspan */
			ffmpeg->width);

		free(input_rows);
	}


	return result;
}



/* assumes 16-bit, interleaved data */
/* always moves buffer */
int quicktime_decode_audio3(
		AVCodecContext *avctx, int16_t *samples,
		int *frame_size_ptr, AVPacket *avpkt)
{
	int ret, got_frame = 0;
	AVFrame *frame = av_frame_alloc();
	if (!frame) return -1;

	ret = avcodec_decode_audio4(avctx, frame, &got_frame, avpkt);

	if( ret >= 0 && got_frame ) {
		int ch, plane_size;
		int planar = av_sample_fmt_is_planar(avctx->sample_fmt);
		int data_size = av_samples_get_buffer_size(&plane_size, avctx->channels,
					   frame->nb_samples, avctx->sample_fmt, 1);
		if( *frame_size_ptr < data_size ) {
			printf("quicktime_decode_audio3: output buffer size is too small for "
				"the current frame (%d < %d)\n", *frame_size_ptr, data_size);
			av_frame_free(&frame);
			return -1;
		}
		memcpy(samples, frame->extended_data[0], plane_size);
		*frame_size_ptr = data_size;
	} else {
		*frame_size_ptr = 0;
	}
	av_frame_free(&frame);
	return ret;
}




