NAME := all_in_one

ROOTDIR := ..

include $(ROOTDIR)/$(NAME)/version.mak
CFLAGS += -DMAJOR_VERSION=$(MAJOR_VERSION)
CFLAGS += -DMINOR_VERSION=$(MINOR_VERSION)
CFLAGS += -DBUILD_NUMBER=$(BUILD_NUMBER)

CFLAGS += -DLOGGER_ENABLE_STDERR

# comment/uncomment to set default debug level
CFLAGS += -DDEBUG_LEVEL_DEFAULT=10

#SOURCES_DIRS += $(ROOTDIR)/$(NAME)
#SOURCES_DIRS += .
SOURCES += main.cpp

SOURCES_DIRS += $(ROOTDIR)/task_a
SOURCES += task_a.cpp

SOURCES_DIRS += $(ROOTDIR)/task_b
SOURCES += task_b.cpp

SOURCES_DIRS += $(ROOTDIR)/utils
SOURCES += debug.c
SOURCES += gettid.c
SOURCES += global.cpp
SOURCES += logger.c
SOURCES += signal_handlers.cpp
SOURCES += time.c

LIBS += pthread
LIBS += rt

# Hide symbols obtained from statically linked libraries to avoid
# conflicts with dynamically loaded components depending on similar
# symbols from shared libraries with different versions
LDFLAGS += -Wl,--exclude-libs,ALL

include $(ROOTDIR)/$(NAME)/common.mak
