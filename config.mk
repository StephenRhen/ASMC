
# Change this to the location of the top level of the source tree
SRCDIR = /home/srhen/Documents/Projects/StateMachines/ASMC

# Change this to match path set in Arduino IDE
USER_LIB_PATH = /home/srhen/Documents/Arduino/libraries

# Paths for GNU-Linux
ADRUINO_DIR = /usr/share/arduino
AVR_TOOLS_DIR = /usr
ARDMK_DIR = /usr/share/arduino

# Optional on GNU-Linux to use avrdude that came with system, rather
# than the version that cam with Arduino.
AVRDUDE = /usr/bin/avrdude
AVRDUDE_CONF = /etc/avrdude.conf

# Paths for Windows
# ARDUINO_DIR   = C:/Arduino
# AVR_TOOLS_DIR = C:/Arduino/hardware/tools/avr
# ARDMK_DIR     = /cygdrive/c/Users/"YourUser"/Arduino-Makefile

# Paths for MAC
# ARDUINO_DIR   = /Applications/Arduino.app/Contents/Java
# ARDMK_DIR     = /usr/local

BOARD_TAG = uno
 
ASMC := $(SRCDIR)/src/asmc
