CXX = g++
CXXFLAGS = -std=c++17 -pedantic -fsanitize=address -Iexamples
LDFLAGS = -lncurses
OBJS = src/CPrint.o src/CGhost.o src/ConfigurationManagement.o src/CUIMenu.o src/CUtilities.o src/main.o
TARGET = vascamat
DOC_DIR = doc
BIN=./main
DOXYFILE = Doxyfile

# Default target
all: compile doc

compile: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# srcfiles
src/CPrint.o: src vascamat/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/CGhost.o: src vascamat/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/ConfigurationManagement.o: src vascamat/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/CUIMenu.o: src vascamat/src vascamat/src vascamat/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/CUtilities.o: src vascamat/src vascamat/src vascamat/src vascamat/src vascamat/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/main.o: src vascamat/src vascamat/src
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: compile
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(DOC_DIR)

.PHONY: doc
doc:
	mkdir -p $(DOC_DIR)
	doxygen $(DOXYFILE)

