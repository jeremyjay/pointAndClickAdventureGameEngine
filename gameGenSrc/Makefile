CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 `wx-config --cxxflags`
# CXXFLAGS = -std=c++11 -Wall -g `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`

TARGET = draw_squares_app
SOURCES = main.cpp toolsPanel.cpp drawObjectsPanel.cpp interactiveObject.cpp common.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
