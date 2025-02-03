# Object files location. Object files will be placed in this directory during compilation
OBJDIR := objects
# Full names of object files
OBJECTS	:= $(addprefix $(OBJDIR)/, Lists.o List.o Float.o String.o Person.o Integer.o Data_Type.o)

CC := gcc

CFLAGS := -g -c
ALL_CFLAGS := -Wall -Wextra -pedantic-errors -fPIC -O2 $(CFLAGS)

# Using an archiver to produce a static library
AR := ar
# Archiver flags
ARFLAGS := -r -s

# ================================================================ #

# Generating a list of all header files in the `include` directory and its subdirectories
INCLUDE := $(wildcard include/*.h)

# Library name
LIB_NAME := lls

# *nix operating system support only
OS_NAME := $(shell uname -s)

# If the operating system is Linux, set the variables
ifeq ($(OS_NAME), Linux)
# The prefix for library names
	LIB_PREFIX := lib
# The suffix for static library files
    LIB_SUFFIX := .a
# The suffix for dynamic library files
    DLL_SUFFIX := .so
else ifeq ($(OS_NAME), Darwin)
# The prefix for library names
    LIB_PREFIX := lib
# The suffix for static library files
    LIB_SUFFIX := .a
# The suffix for dynamic library files
    DLL_SUFFIX := .dylib
else
    $(error Unsupported operating system)
endif

# Constructing the name of static library
TARGET_STATIC := $(LIB_PREFIX)$(LIB_NAME)$(LIB_SUFFIX)

# Constructing the name of static library
TARGET_SHARED := $(LIB_PREFIX)$(LIB_NAME)$(DLL_SUFFIX)

# ================================================================ #

# Define a target
all: $(TARGET_STATIC) $(TARGET_SHARED)

# Building a static library
$(TARGET_STATIC): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

#Building a shared library
$(TARGET_SHARED): $(OBJECTS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# ================================================================ #
# ======================== START BUILDING ======================== #
# ================================================================ #

DATA  := src/Types/Float/Float.c src/Types/Integer/Integer.c src/Types/String/String.o src/Types/User/Person.c src/Types/Data_Type.c

$(OBJDIR)/Lists.o: src/Lists/Lists.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

$(OBJDIR)/List.o: src/Lists/Singly/List.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

$(OBJDIR)/Float.o: src/Types/Float/Float.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

$(OBJDIR)/Integer.o: src/Types/Integer/Integer.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

$(OBJDIR)/String.o: src/Types/String/String.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

$(OBJDIR)/Person.o: src/Types/User/Person.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

$(OBJDIR)/Data_Type.o: src/Types/Data_Type.c $(INCLUDE)
	$(CC) $(ALL_CFLAGS) -o $@ $<

# ================================================================ #

# Creating a directory if it does not exist. *nix
$(shell mkdir -p $(OBJDIR))

# Executing the commands regardless of whether a file named clean exists or not
.PHONY: clean

clean:
	rm -rf $(OBJS) $(OBJDIR) $(TARGET_STATIC) $(TARGET_SHARED) *.out
