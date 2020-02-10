CXX ?= c++-9

SRC_PATH = lib
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

BIN_NAME = rbhash

SRC_EXT = cpp

# Find all source files sorted by most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

INCLUDES = -I./include/
LIBS = 
COMPILE_FLAGS = -std=c++11 -O3 $(INCLUDES)

DEBUG =

.PHONY: default_target
default_target: release

release: export CXXFLAGS := $(DEBUG) $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

.PHONY: debug
debug: DEBUG = -DDEBUG=1 -g -Wall -Wextra -pedantic
debug: export CXXFLAGS := $(DEBUG) $(CXXFLAGS) $(COMPILE_FLAGS)
debug:
	@echo "debug activated"
	@echo " "
	@$(MAKE) clean
	@$(MAKE) dirs
	@$(MAKE) all

# checks the executable and symlinks to the output
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)
	@echo " "

# Creation of the executable link
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(CXXFLAGS) $(OBJECTS) main.cpp -o $@
	@echo " "

# Add dependency files, if they exist
-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $< -o $@
	@echo " "
