
TOPDIR := $(shell pwd)

FAAC_PATH := $(shell cd faac*; pwd)
FAAD_PATH := $(shell cd faad2*; pwd)
LAME_PATH := $(shell cd lame*; pwd)
VORBIS_PATH := $(shell cd libvorbis*; pwd)
X264_PATH := $(shell cd x264*; pwd)
DV_PATH := $(shell cd libdv*; pwd)
OGG_PATH := $(shell cd libogg*; pwd)
JPEG_MMX_PATH := $(shell cd jpeg-mmx*; pwd)
FFMPEG_PATH := $(shell cd ffmpeg*; pwd)

TARGETS := \
	libdv \
	libogg \
	jpeg-mmx \
	ffmpeg \

all:	$(TARGETS)

# faad
.PHONY:	faad faad-configure
faad-configure: $(FAAD_PATH)/.configure
faad: $(FAAD_PATH)/.built

$(FAAD_PATH)/.configure:
	@echo "CONFIGURING FAAD"
	cd $(FAAD_PATH) && \
		./configure && \
		sed 's/       /\t/' Makefile > Makefile2 && mv -f Makefile2 Makefile
	touch $@

$(FAAD_PATH)/.built:	$(FAAD_PATH)/.configure
	+make -C $(FAAD_PATH)
	touch $@



# faac
.PHONY:	faac faac-configure
faac-configure: $(FAAC_PATH)/.configure
faac:	$(FAAC_PATH)/.built

$(FAAC_PATH)/.configure:
	@echo "CONFIGURING FAAC"
	cd $(FAAC_PATH) && \
		./configure
	touch $@

$(FAAC_PATH)/.built:	$(FAAC_PATH)/.configure
	+make -C $(FAAC_PATH)
	touch $@



# lame
.PHONY:	lame lame-configure
lame-configure: $(LAME_PATH)/.configure
lame:	$(LAME_PATH)/.built

$(LAME_PATH)/.configure:
	@echo "CONFIGURING LAME"
	cd $(LAME_PATH) && \
		./configure
	touch $@

$(LAME_PATH)/.built:	$(LAME_PATH)/.configure
	+make -C $(LAME_PATH)
	cd $(LAME_PATH)/include ; ln -s . lame
	touch $@



# vorbis
.PHONY:	vorbis vorbis-configure
vorbis-configure: $(VORBIS_PATH)/.configure
vorbis:	$(VORBIS_PATH)/.built

$(VORBIS_PATH)/.configure:
	@echo "CONFIGURING VORBIS"
	cd $(VORBIS_PATH) && \
		CFLAGS="-I$(OGG_PATH)/include -L$(OGG_PATH)/src/" \
			./configure --disable-oggtest --enable-shared=no
	touch $@

$(VORBIS_PATH)/.built:	$(VORBIS_PATH)/.configure
	+make -C $(VORBIS_PATH)
	touch $@



# x264
.PHONY:	x264 x264-configure
x264-configure: $(X264_PATH)/.configure
x264:	$(X264_PATH)/.built

$(X264_PATH)/.configure:
	@echo "CONFIGURING X264"
	cd $(X264_PATH) && \
		./configure --enable-static
	touch $@

$(X264_PATH)/.built:	$(X264_PATH)/.configure
	+make -C $(X264_PATH)
	touch $@



# libdv
.PHONY:	libdv libdv-configure
libdv-configure: $(DV_PATH)/.configure
libdv:	$(DV_PATH)/.built

$(DV_PATH)/.configure:
	@echo "CONFIGURING DV"
	cd $(DV_PATH) && \
		./configure --disable-gtk --enable-shared=no
	touch $@

$(DV_PATH)/.built: $(DV_PATH)/.configure
	+make -C $(DV_PATH)
	touch $@


# libogg
.PHONY:	libogg libogg-configure
libogg-configure: $(OGG_PATH)/.configure
libogg:	$(OGG_PATH)/.built

$(OGG_PATH)/.configure:
	@echo "CONFIGURING OGG"
	cd $(OGG_PATH) && \
		./configure
	touch $@

$(OGG_PATH)/.built:	$(OGG_PATH)/.configure
	+make -C $(OGG_PATH)
	touch $@



# jpeg-mmx
.PHONY:	jpeg-mmx jpeg-mmx-configure
jpeg-mmx-configure: $(JPEG_MMX_PATH)/.configure
jpeg-mmx:	$(JPEG_MMX_PATH)/.built

$(JPEG_MMX_PATH)/.configure:
	@echo "CONFIGURING JPEG-MMX"
	cd $(JPEG_MMX_PATH) && \
		./configure
	touch $@

$(JPEG_MMX_PATH)/.built:	$(JPEG_MMX_PATH)/.configure
	+make -C $(JPEG_MMX_PATH)
	touch $@



# ffmpeg
.PHONY:	ffmpeg ffmpeg-configure
ffmpeg-configure: $(FFMPEG_PATH)/.configure
ffmpeg:	$(FFMPEG_PATH)/.built

$(FFMPEG_PATH)/.configure: \
		$(FAAD_PATH)/.built \
		$(FAAC_PATH)/.built \
		$(LAME_PATH)/.built \
		$(VORBIS_PATH)/.built \
		$(X264_PATH)/.built \

	@echo "CONFIGURING FFMPEG"
	cd $(FFMPEG_PATH) && \
		./configure \
			--enable-pthreads --enable-gpl \
			--disable-ffserver --disable-ffplay \
			--enable-libfaac \
			--enable-libmp3lame \
			--enable-libvorbis \
			--enable-libx264 \
			--enable-nonfree \
			--extra-cflags="\
				-I$(FAAD_PATH)/include \
				-I$(FAAC_PATH)/include \
				-I$(LAME_PATH)/include \
				-I$(VORBIS_PATH)/include \
				-I$(X264_PATH)" \
			--extra-libs="\
				-L$(FAAD_PATH)/libfaad/.libs/ \
				-L$(FAAC_PATH)/libfaac/.libs/ \
				-L$(LAME_PATH)/libmp3lame/.libs/ \
				-L$(VORBIS_PATH)/lib/.libs/ \
				-L$(X264_PATH) -ldl" \
			--extra-ldflags="-ldl"
	touch $@

$(FFMPEG_PATH)/.built:	$(FFMPEG_PATH)/.configure
	+make -C $(FFMPEG_PATH)
	touch $@

