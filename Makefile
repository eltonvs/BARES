# DIRS
INCDIR = include
BINDIR = bin
SRCDIR = src
T_SRCDIR = tests
BUILDDIR = build
T_BUILDDIR = tests_build
LIBDIR = lib
# LIB OPTIONS
# TARGET
TARGET = $(BINDIR)/bares
T_TARGET = $(BINDIR)/tests_bares
# EXTENSIONS
SRCEXT = cpp
HEADEREXT = hpp
# SOURCES LIST
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
T_SOURCES = $(shell find $(T_SRCDIR) -type f -name *.$(SRCEXT))
# OBJECTS
OBJS = $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
T_OBJS = $(patsubst $(T_SRCDIR)/%, $(T_BUILDDIR)/%, $(T_SOURCES:.$(SRCEXT)=.o))
# COMPILER
CC = g++
# FOR CLEANING
RM = /bin/rm
# WARNING FLAG
WARN = -Wall
# DEBUG FLAGS
DEBUG = -g
# LINKING FLAGS
LIBOPTS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
LIBFLAG = -L $(LIBDIR) $(LIBOPTS)
INCFLAG = -I $(INCDIR)
LFLAGS = $(DEBUG) $(WARN) $(INCFLAG) # $(LIBFLAG)
# COMPILATION FLAGS
CFLAGS = $(DEBUG) -c $(WARN) -std=c++11

# ----------------------
# ENTRIES
# ----------------------

main: $(TARGET)

tests: $(T_TARGET)

# Main Version
$(TARGET): $(OBJS)
	@echo "Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LFLAGS)"; $(CC) $^ -o $(TARGET) $(LFLAGS)
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<"; $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<

# Tests Version
$(T_TARGET): $(T_OBJS)
	@echo "Linking..."
	@echo " $(CC) $^ -o $(T_TARGET) $(LFLAGS)"; $(CC) $^ -o $(T_TARGET) $(LFLAGS)
$(T_BUILDDIR)/%.o: $(T_SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(T_BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<"; $(CC) $(CFLAGS) $(INCFLAG) -o $@ $<

# DUMMY ENTRIES
clean:
	@echo "Cleaning..."
	@echo " $(RM) -r $(OBJS) $(TARGET) $(T_OBJS) $(T_TARGET)"; $(RM) -r $(OBJS) $(TARGET) $(T_OBJS) $(T_TARGET)

.PHONY: clean
