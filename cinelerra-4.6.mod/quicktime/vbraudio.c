// Utility functions for vbr audio

#include "funcprotos.h"
#include "quicktime.h"



// Maximum samples to store in output buffer
#define MAX_VBR_BUFFER 0x200000



void quicktime_init_vbr(quicktime_vbr_t *vbr, int channels)
{
	vbr->channels = channels;
	if(!vbr->output_buffer)
	{
		int i;
		vbr->output_buffer = calloc(channels, sizeof(double*));
		for(i = 0; i < channels; i++)
			vbr->output_buffer[i] = calloc(MAX_VBR_BUFFER, sizeof(double));
	}
}

void quicktime_clear_vbr(quicktime_vbr_t *vbr)
{
	int i;

	if(vbr->output_buffer)
	{
		for(i = 0; i < vbr->channels; i++)
			free(vbr->output_buffer[i]);
		free(vbr->output_buffer);
	}

	if(vbr->input_buffer)
	{
		free(vbr->input_buffer);
	}
}

void quicktime_vbr_set_channels(quicktime_vbr_t *vbr, int channels)
{
	vbr->channels = channels;
}

int64_t quicktime_vbr_end(quicktime_vbr_t *vbr)
{
	return vbr->buffer_end;
}

unsigned char* quicktime_vbr_input(quicktime_vbr_t *vbr)
{
	return vbr->inp_ptr;
}

int quicktime_vbr_input_size(quicktime_vbr_t *vbr)
{
	return vbr->input_size;
}

static int limit_samples(int samples)
{
	if(samples > MAX_VBR_BUFFER)
	{
		fprintf(stderr, "quicktime_align_vbr: "
			"can't decode more than 0x%x samples at a time.\n",
			MAX_VBR_BUFFER);
		return 1;
	}
	return 0;
}

int quicktime_align_vbr(quicktime_audio_map_t *atrack, 
	int samples)
{
	quicktime_vbr_t *vbr = &atrack->vbr;
	int64_t start_position = atrack->current_position;

	if(limit_samples(samples)) return 1;

// Desired start point is outside existing range.  Reposition buffer pointer
// to start time of nearest frame.
	if(start_position < vbr->buffer_end - vbr->buffer_size ||
		start_position > vbr->buffer_end)
	{
		int64_t start_time = start_position;
		vbr->sample = quicktime_time_to_sample(&atrack->track->mdia.minf.stbl.stts,
			&start_time);
		vbr->buffer_end = start_time;
		vbr->buffer_size = 0;
		vbr->inp_ptr = vbr->input_buffer;
		vbr->input_size = 0;
	}

	return 0;
}

int quicktime_read_vbr(quicktime_t *file,
	quicktime_audio_map_t *atrack)
{
	quicktime_vbr_t *vbr = &atrack->vbr;
	quicktime_trak_t *trak = atrack->track;
        quicktime_stts_t *stts = &trak->mdia.minf.stbl.stts;
	int64_t offset = quicktime_sample_to_offset(file, 
		trak, 
		vbr->sample);
	int size = quicktime_sample_size(trak, vbr->sample);
	int new_allocation = vbr->input_size + size;
	int result = 0;

	if(vbr->input_allocation < new_allocation)
	{
		int inp_offset = !vbr->input_buffer ? 0 :
			 vbr->inp_ptr - vbr->input_buffer;
		vbr->input_buffer = realloc(vbr->input_buffer, new_allocation);
		vbr->input_allocation = new_allocation;
		vbr->inp_ptr = vbr->input_buffer + inp_offset;
	}


	quicktime_set_position(file, offset);
	result = !quicktime_read_data(file, (char*)vbr->inp_ptr + vbr->input_size, size);
	vbr->input_size += size;
	offset = vbr->buffer_end;
        vbr->buffer_end = quicktime_chunk_to_samples(stts, ++vbr->sample);
	vbr->buffer_size += vbr->buffer_end - offset;
	return result;
}

void quicktime_shift_vbr(quicktime_audio_map_t *atrack, int bytes)
{
	quicktime_vbr_t *vbr = &atrack->vbr;
	if(bytes >= vbr->input_size)
	{
		vbr->inp_ptr = vbr->input_buffer;
		vbr->input_size = 0;
	}
	else
	{
		vbr->inp_ptr += bytes;
		vbr->input_size -= bytes;
	}
}

void quicktime_store_vbr_float(quicktime_audio_map_t *atrack,
	float *samples,
	int sample_count)
{
	int i, j;
	quicktime_vbr_t *vbr = &atrack->vbr;
	for(i = 0; i < sample_count; i++)
	{
		for(j = 0; j < vbr->channels; j++)
		{
			vbr->output_buffer[j][vbr->buffer_ptr] = 
				samples[i * vbr->channels + j];
		}
		vbr->buffer_ptr++;
		if(vbr->buffer_ptr >= MAX_VBR_BUFFER)
			vbr->buffer_ptr = 0;
	}
	vbr->buffer_end += sample_count;
	vbr->buffer_size += sample_count;
	if(vbr->buffer_size > MAX_VBR_BUFFER) vbr->buffer_size = MAX_VBR_BUFFER;
}

void quicktime_store_vbr_int16(quicktime_audio_map_t *atrack,
	int16_t *samples,
	int sample_count)
{
	int i, j;
	quicktime_vbr_t *vbr = &atrack->vbr;
	for(i = 0; i < sample_count; i++)
	{
		for(j = 0; j < vbr->channels; j++)
		{
			vbr->output_buffer[j][vbr->buffer_ptr] = 
				(float)samples[i * vbr->channels + j] / 32768.0;
		}
		vbr->buffer_ptr++;
		if(vbr->buffer_ptr >= MAX_VBR_BUFFER)
			vbr->buffer_ptr = 0;
	}
	vbr->buffer_end += sample_count;
	vbr->buffer_size += sample_count;
	if(vbr->buffer_size > MAX_VBR_BUFFER) vbr->buffer_size = MAX_VBR_BUFFER;
}

void quicktime_copy_vbr_float(quicktime_vbr_t *vbr,
	int64_t start_position, 
	int samples,
	float *output, 
	int channel)
{
	int i;
	int input_ptr = vbr->buffer_ptr - 
		(vbr->buffer_end - start_position);
	while(input_ptr < 0) input_ptr += MAX_VBR_BUFFER;

	for(i = 0; i < samples; i++)
	{
		output[i] = vbr->output_buffer[channel][input_ptr++];
		if(input_ptr >= MAX_VBR_BUFFER)
			input_ptr = 0;
	}
}


void quicktime_copy_vbr_int16(quicktime_vbr_t *vbr,
	int64_t start_position, 
	int samples,
	int16_t *output, 
	int channel)
{
	int i;
	int input_ptr = vbr->buffer_ptr - 
		(vbr->buffer_end - start_position);
	while(input_ptr < 0) input_ptr += MAX_VBR_BUFFER;
	for(i = 0; i < samples; i++)
	{
		output[i] = (int)(vbr->output_buffer[channel][input_ptr++] * 32767);
		if(input_ptr >= MAX_VBR_BUFFER)
			input_ptr = 0;
	}
}



