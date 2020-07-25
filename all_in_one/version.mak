VERSION_FILE  := $(ROOTDIR)/$(NAME)/vers.ion
MAJOR_VERSION := $(shell sed -n "/^MAJOR_VERSION.*/ s/.*=//p" $(VERSION_FILE))
MINOR_VERSION := $(shell sed -n "/^MINOR_VERSION.*/ s/.*=//p" $(VERSION_FILE))
# BUILD_NUMBER from 'environment' has precedence over BUILD_NUMBER from 'VERSION_FILE'
ifeq (,$(strip $(BUILD_NUMBER)))
BUILD_NUMBER := $(shell sed -n "/^BUILD_NUMBER.*/ s/.*=//p" $(VERSION_FILE))
endif
