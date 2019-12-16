
include ../../config.mk

EXAMPLE = Led2

SKETCH = $(addsuffixex .ino,$(EXAMPLE))
SKETCH_OBJ = $(addsuffix .o,$(SKETCH))

SM_CLASS = $(addsuffix Sm,$(EXAMPLE))
SM_SRC = $(addsuffix .sm,$(SM_CLASS))
SM_TRACEFILE = $(addsuffix .tf,$(SM_CLASS))
SM_CPP_FILE = $(addsuffix .cpp,$(SM_CLASS))
SM_INCLUDE = $(addsuffix .h,$(SM_CLASS))

# Specify the sources, the arduino make system can not find
# the state machine class file on a clean build because
# it doesn't exist
LOCAL_CPP_SRCS = $(SM_CPP_FILE)

# If you specify the sources you need to manually provide
# the libraries.
ARDUINO_LIBS = Button

include $(ARDMK_DIR)/Arduino.mk

$(OBJDIR)/$(SKETCH_OBJ):  $(SM_INCLUDE)

$(SM_CPP_FILE) $(SM_INCLUDE): $(SM_SRC) $(ASMC)
	$(ASMC) -t$(SM_TRACEFILE) $<

clean::
	rm -f $(SM_CPP_FILE) $(SM_INCLUDE) $(SM_TRACEFILE) *~
