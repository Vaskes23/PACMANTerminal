CXX = g++
CXXFLAGS = -std=c++17 -pedantic -fsanitize=address -Iexamples
LDFLAGS = -lncurses
OBJS = src/CPrint.o src/CGhost.o src/ConfigurationManagement.o src/CUIMenu.o src/CMove.o src/main.o
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
src/CPrint.o: src/CPrint.cpp src/CPrint.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/CGhost.o: src/CGhost.cpp src/CGhost.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/ConfigurationManagement.o: src/ConfigurationManagement.cpp src/ConfigurationManagement.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/CUIMenu.o: src/CUIMenu.cpp src/CUIMenu.h src/CPrint.h src/ConfigurationManagement.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/CMove.o: src/CMove.cpp src/CMove.h src/CPrint.h src/CGhost.h src/ConfigurationManagement.h src/CUIMenu.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/main.o: src/main.cpp src/CUIMenu.h src/CMove.h
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

