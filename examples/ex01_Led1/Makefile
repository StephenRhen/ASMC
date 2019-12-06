

include ../../config.mk

# Specify the sources, arduino make will not pick it
# up on a clean build.
LOCAL_CPP_SRCS = LedSm.cpp

# If you specify the sources you need to manually provide
# the libraries.
ARDUINO_LIBS = Button

include $(ARDMK_DIR)/Arduino.mk

all: LedSm.cpp LedSm.h

$(OBJDIR)/led.ino.o: LedSm.h

LedSm.cpp LedSm.h: LedSm.sm $(ASMC)
	$(ASMC) -tLedSm.tf $<

clean::
	rm -f LedSm.cpp LedSm.h LedSm.tf *~

