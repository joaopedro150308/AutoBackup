CC = gcc
CFLAGS = -Wall -Wextra -I./src
LDFLAGS = -lshlwapi -mconsole
OBJPATH = build
TARGET = app

LIBS = -shlwapi

# Fontes
SRCS := $(wildcard src/*/*.c)
# Cabecálhos
HDRS := $(patsubst src/%.c, src/%.h, $(SRCS))
# Objetos
OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o build/$@
	
build/%.o: src/%.c src/%.h
	if not exist $(subst /,\, $(@D)) mkdir $(subst /,\, $(@D))
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /q $(OBJPATH)\ *.o