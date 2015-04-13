include ../../global_config

OBJS = $(OBJDIR)/livevideo.o
DV_DIR := $(shell cd ../../thirdparty/libdv*; pwd)
JPEG_DIR := $(shell cd ../../thirdparty/jpeg; pwd)
CFLAGS += -I$(DV_DIR) -I$(JPEG_DIR)

OUTPUT = $(PLUGIN_DIR)/livevideo.plugin

include ../../plugin_config


$(OBJDIR)/livevideo.o: livevideo.C
