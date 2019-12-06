CXX = g++
CXXFLAGS = -Wall -Werror -std=c++17 -Iinclude
RELEASE_FLAGS = -O3 -DNDEBUG
DEBUG_FLAGS = -g
LDFLAGS = -lglut -lGLU -lGL

EXE = main
SRCDIR = src
BINDIR = bin
RELEASE_DIR = release
DEBUG_DIR = debug
BINARY = bin
EXE_NAME = main

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

ifeq ($(RELEASE), 1)
CXXFLAGS += $(RELEASE_FLAGS)
BINDIR = $(RELEASE_DIR)/$(BINARY)
EXE = $(RELEASE_DIR)/$(EXE_NAME)
else ifeq ($(DEBUG), 1)
CXXFLAGS += $(DEBUG_FLAGS)
BINDIR = $(DEBUG_DIR)/$(BINARY)
EXE = $(DEBUG_DIR)/$(EXE_NAME)
else

endif

all: $(EXE)

release:
	make RELEASE=1

debug:
	make DEBUG=1

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE) $(RELEASE_DIR) $(DEBUG_DIR)

.PHONY: clean all release debug
