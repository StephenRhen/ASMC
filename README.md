
# ASMC - Another State Machine Compiler

  The ASMC generates code for small efficient 
event driven state machines
  primarily for for micro-controllers. The compiler takes a state machine
  description file and creates a c++ class from it. Although the tutorial
  and examples are all for Arduino systems, the code generated is generic
  and can be compile for any system.

## Features

- ### Flexible Actions
User code can be executed on transition events as well as entry or exit
from a state.

- ### State Variables
User defined state variables are supported.

## Missing

- ### No pre-built executable.
The package should compile on any system with a basic GNU Unix style
development environment. The tools required to build the compiler are 'make',
'flex', 'bison', and 'gcc'. Additionally you will need to have Arduino
installed to build the examples. I don't use Windows or Mac OS, if some
brave soul wishes to contribute Windows or Mac support to the project that
would be most appreciated.

## Installation

### System Requirements
* GNU utilities gcc, make, bison and flex
* [Arduino-Makefile v1.6.0](https://github.com/sudar/Arduino-Makefile/releases/tag/1.6.0)

### Setup
Down load the repository and edit 'config.mk' to set SRCDIR and
USR_LIB_PATH. Select the other variables as appropriate for your OS type. 
You may need to adjust some of the other variables based on your
local configuration.

### Building
Run **make** in the top level project directory to build the compiler and
all of the example scripts. If you don't wish to build the examples change
to the **src** directory and run **make** 


