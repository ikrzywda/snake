# generated with gpt-3.5

# Compiler and linker flags
CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror
LDFLAGS := -lstdc++ -fsanitize=address

SFML_INCLUDE_DIR := /usr/local/include
SFML_LIBRARY_DIR := /usr/local/lib

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system


CLANG_FORMAT = clang-format
CLANG_FORMAT_FLAGS = -style=google
CPP_EXTENSIONS = cpp hpp 

# Source files and directories
SRCDIR := src
FMT_SRCS := $(wildcard $(SRCDIR)/*)
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix build/,$(notdir $(SRCS:.cpp=.o)))
EXEC := build/myapp


.PHONY: all clean

# Default target
all: $(EXEC)

# Linking target
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ -L$(SFML_LIBRARY_DIR) $(LDLIBS)

# Compilation targets
build/%.o: $(SRCDIR)/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -I$(SFML_INCLUDE_DIR) -o $@

build:
	mkdir -p $@

run: $(EXEC)
	./$(EXEC)

.PHONY: format
format:
	$(CLANG_FORMAT) $(CLANG_FORMAT_FLAGS) $(FMT_SRCS) -i

# Clean target
clean:
	rm -rf build

