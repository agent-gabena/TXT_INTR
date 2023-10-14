.PHONY: all debug release clean
NAME = calculator
LIBRARIES = -l boost_program_options
DEBUG = -g -Wall
RELEASE = -Wall -DNDEBUG
DB_EXEC = $(NAME)-dbg
RL_EXEC = $(NAME)
SOURCE = *.cpp
all: debug release
debug: $(DB_EXEC)
release: $(RL_EXEC)
clean:
	rm -f $(RL_EXEC) $(DB_EXEC)
$(DB_EXEC): $(SOURCE)
	g++ $(DEBUG) $(SOURCE) $(LIBRARIES) -o $(DB_EXEC)

$(RL_EXEC): $(SOURCE)
	g++ $(RELEASE) $(SOURCE) $(LIBRARIES) -o $(RL_EXEC)