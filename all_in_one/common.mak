.PHONY: default all clean

# Let's use '.SECONDEXPANSION:' for substitutions in prerequisites
.SECONDEXPANSION:

# Common targets
default: all

# Main definitions
BUILD_DIR = $(ROOTDIR)/$(NAME)/BUILD_DIR
INSTALL_DIR = $(ROOTDIR)/$(NAME)/INSTALL_DIR
EXECUTABLE = $(INSTALL_DIR)/$(NAME)

# search $(SOURCES) in $(SOURCES_DIRS)
vpath %.c $(SOURCES_DIRS)
vpath %.cpp $(SOURCES_DIRS)

# search include files next to sources
INCLUDE += $(SOURCES_DIRS)

OBJECTS := $(patsubst %,$(BUILD_DIR)/%.o,$(SOURCES))
OBJECTS_DIRS := $(sort $(dir $(OBJECTS)))

CC := gcc
CXX := g++

CXXFLAGS += -std=c++11

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -Wno-format-zero-length
CFLAGS += -g
CFLAGS += -O2
CFLAGS += -fvisibility=hidden

CFLAGS += $(addprefix -isystem , $(SYS_INCLUDE))
CFLAGS += $(addprefix -iquote , $(INCLUDE))

# Generate dependencies
CFLAGS += -MMD

# Load dependencies if present
-include $(OBJECTS:.o=.d)

#LDFLAGS += -Wl,-Map=$@.map
LDFLAGS += -Wl,--as-needed
LDFLAGS += $(addprefix -L, $(LIB_DIRS))
LDFLAGS += $(addprefix -l, $(LIBS))

all: $(EXECUTABLE)

# Main executable
$(EXECUTABLE): $(OBJECTS) | $$(dir $$@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# C sources compilation
$(BUILD_DIR)/%.c.o : %.c | $$(dir $$@)
	$(CC) -c $(CFLAGS) -o $@ $<

# C++ sources compilation
$(BUILD_DIR)/%.cpp.o: %.cpp | $$(dir $$@)
	$(CXX) -c $(CXXFLAGS) $(CFLAGS) -o $@ $<

# Directories for object files and binaries
BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS) $(dir $(EXECUTABLE)))
#$(info BUILD_SUBDIRS="$(BUILD_SUBDIRS)")
$(BUILD_SUBDIRS):
	mkdir -pv $@

clean:
	-rm -rf $(INSTALL_DIR) $(BUILD_DIR)
