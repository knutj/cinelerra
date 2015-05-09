include ../../global_config

OBJS = $(OBJDIR)/brighttheme.o
THEME_DATA := $(OBJDIR)/brighttheme_data.o

OUTPUT_THEME := $(PLUGIN_DIR)/brighttheme.plugin
AVC_DIR := $(shell cd ../../thirdparty/libavc*; pwd)

CFLAGS += -I$(AVC_DIR)

$(OUTPUT_THEME): $(OBJS) $(THEME_DATA)
	$(LDLINKER) -o $(OUTPUT_THEME) $(OBJS) $(THEME_DATA)
	$(if $(findstring -g,$(CFLAGS)),,strip $(OUTPUT_THEME))



include ../../plugin_config

$(OBJDIR)/brighttheme.o: brighttheme.C

$(THEME_DATA):
	cd $(OBJDIR) && \
	../../../guicast/$(OBJDIR)/bootstrap brighttheme_data.o ../data/*.png

inst:
	rm -f ../../bin/brighttheme.plugin
	cp $(OUTPUT_THEME) ../../bin/



