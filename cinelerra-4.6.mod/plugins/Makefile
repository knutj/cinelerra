include ../global_config

# burn must come before any other effecttv plugin
# colors must come before any plugin
# parametric must come before fourier plugins
# motion must come before perspective

DIRS = \
	1080to480 \
	1080to540 \
	720to480 \
	aging \
	audioscope \
	bandslide \
	bandwipe \
	blondtheme \
	bluebanana \
	bluedottheme \
	blur \
	brightness \
	brighttheme \
	burn \
	C41 \
	cdripper \
	chromakey \
	chromakeyhsv \
	color3way \
	colorbalance \
	compressor \
	crossfade \
	dcoffset \
	decimate \
	deinterlace \
	deinterlace-cv \
	delayaudio \
	delayvideo \
	denoise \
	denoisefft \
	denoisemjpeg \
	denoiseseltempavg \
	denoisevideo \
	despike \
	diffkey \
	dissolve \
	dot \
	downsample \
	echo \
	echocancel \
	fieldframe \
	flash \
	flip \
	framefield \
	freeverb \
	freezeframe \
	gain \
	gamma \
	gradient \
	graphic \
	greycstoration \
	histogram \
	holo \
	huesaturation \
	interpolate \
	interpolateaudio \
	interpolatevideo \
	invertaudio \
	invertvideo \
	irissquare \
	ivtc \
	lens \
	level \
	libeffecttv \
	linearblur \
	liveaudio \
	livevideo \
	loopaudio \
	loopvideo \
	motion \
	motion2point \
	motionblur \
	normalize \
	oilpainting \
	overlay \
	overlayaudio \
	parametric \
	perspective \
	photoscale \
	pitch \
	polar \
	radialblur \
	reframe \
	reframert \
	removegaps \
	reroute \
	resample \
	resamplert \
	reverb \
	reverseaudio \
	reversevideo \
	rgb601 \
	rgbshift \
	rotate \
	scale \
	shapewipe \
	sharpen \
	shiftinterlace \
	slide \
	spectrogram \
	suv \
	svg \
	swapchannels \
	swapframes \
	synthesizer \
	threshold \
	timeavg \
	timefront \
	timestretch \
	timestretchrt \
	titler \
	translate \
	unsharp \
	videoscope \
	vocoder \
	wave \
	whirl \
	wipe \
	yuv \
	yuvshift \
	zoom \
	zoomblur \

#	findobject \

# Make static table of all plugins
ifeq ($(DO_STATIC), y)

endif


all:	$(DIRS)

# parallel compilation of all directories
.PHONY:	$(DIRS)
$(DIRS):
	$(MAKE) -C $@

clean:
	rm -rf $(foreach d,$(DIRS),$(d)/$(OBJDIR))
	rm -rf ../bin/plugins
	rm -f ../bin/mpeg2enc.plugin

# Can't strip the themes so instead the plugins strip themselves
install:
	mkdir -p ../bin/plugins
	cp -a fonts ../bin/plugins/.
	cp -a shapes ../bin/plugins/.
	cp ../thirdparty/mjpegtools*/mpeg2enc/mpeg2enc ../bin/mpeg2enc.plugin

# dependencies for parallel build
aging:		libeffecttv
burn:		libeffecttv
dot:		libeffecttv
holo:		libeffecttv
motion2point:	downsample motion
motion:		downsample
timestretchrt:	timestretch

