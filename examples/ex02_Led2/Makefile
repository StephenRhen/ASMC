
include ../../config.mk

# Specify the sources, arduino make will not pick it
# up on a clean build.
LOCAL_CPP_SRCS = Led2Sm.cpp

# If you specify the sources you need to manually provide
# the libraries.
ARDUINO_LIBS = Button

include $(ARDMK_DIR)/Arduino.mk

all: Led2Sm.cpp Led2Sm.h

$(OBJDIR)/led.ino.o: Led2Sm.h

Led2Sm.cpp Led2Sm.h: Led2Sm.sm $(ASMC)
	$(ASMC) -tLed2Sm.tf $<

clean::
	rm -f Led2Sm.cpp Led2Sm.h Led2Sm.tf *~
