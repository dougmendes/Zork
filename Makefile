CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Iinclude
TARGET = bin/zork
SRCDIR = src
INCDIR = include
BUILDDIR = build

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: directories $(TARGET)

directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p bin

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) bin
	@echo "Clean complete"

run: all
	./$(TARGET)

rebuild: clean all

# ==========================================
# Windows Cross-Compilation (MinGW)
# ==========================================

# Windows compiler
CXX_WIN = x86_64-w64-mingw32-g++
CXXFLAGS_WIN = -std=c++11 -Wall -Wextra -pedantic -Iinclude -O2
LDFLAGS_WIN = -static-libgcc -static-libstdc++ -static -municode

# Check if MinGW is installed
check-mingw:
	@which $(CXX_WIN) > /dev/null || (echo "Error: MinGW not found. Install with: brew install mingw-w64" && exit 1)

# Compile for Windows (64-bit, fully static)
windows: check-mingw directories
	$(CXX_WIN) $(CXXFLAGS_WIN) $(SOURCES) -o bin/zork.exe $(LDFLAGS_WIN)
	@echo "Windows build complete: bin/zork.exe"
	@file bin/zork.exe

# Alternative: Windows build without unicode (for console apps)
windows-console: check-mingw directories
	$(CXX_WIN) $(CXXFLAGS_WIN) $(SOURCES) -o bin/zork.exe -static-libgcc -static-libstdc++ -mconsole
	@echo "Windows console build complete: bin/zork.exe"
	@file bin/zork.exe

# Clean Windows build
windows-clean:
	rm -f bin/zork.exe


.PHONY: all clean run directories rebuild