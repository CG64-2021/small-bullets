OBJS=main.c m_utils.c object.c
CC=gcc

ICFLAGS=-Isdl2-i686/include/SDL2
ICFLAGS+=-Isdl2-mixer-i686/include/SDL2
ICFLAGS+=-Isdl2-image-i686/include/SDL2
LDFLAGS=-Lsdl2-i686/lib
LDFLAGS+=-Lsdl2-mixer-i686/lib
LDFLAGS+=-Lsdl2-image-i686/lib
LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image

OBJ_NAME=SmallBullets

all:$(OBJS)
	$(CC) $(OBJS) $(ICFLAGS) $(LDFLAGS) $(LIBS) -o $(OBJ_NAME)