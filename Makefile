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

.PHONY: all clean run directories rebuild