CPPFLAGS = -std=c++23
INC = -Iinc
LIBS =
LIBS += -lsfml-graphics
LIBS += -lsfml-network
LIBS += -lsfml-system
LIBS += -lsfml-window
LIBS += -lsfml-audio

HEADERS = $(wildcard inc/*.hpp)
FILES = $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,obj/%.o,$(FILES))
DEPENDS := $(OBJECTS:.o=.d)

bin/sfml: $(OBJECTS)
	g++ $(OBJECTS) -o $@ $(LIBS)

obj/%.o: src/%.cpp
	g++ $(CPPFLAGS) $(INC) -MMD -MP -c $< -o $@

.PHONY: clean

clean:
	rm -f obj/*.o
	rm -f obj/*.d

-include $(DEPENDS)
