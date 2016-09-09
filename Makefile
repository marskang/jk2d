CFLAGS = -Wall -Ilib/zlib -Ilib/libpng

ZLIB := \
lib/zlib/adler32.c \
lib/zlib/compress.c \
lib/zlib/crc32.c \
lib/zlib/deflate.c \
lib/zlib/gzclose.c \
lib/zlib/gzlib.c \
lib/zlib/gzread.c \
lib/zlib/gzwrite.c \
lib/zlib/infback.c \
lib/zlib/inffast.c \
lib/zlib/inflate.c \
lib/zlib/inftrees.c \
lib/zlib/trees.c \
lib/zlib/uncompr.c \
lib/zlib/zutil.c \


LIBPNG := \
lib/libpng/png.c \
lib/libpng/pngerror.c \
lib/libpng/pngget.c \
lib/libpng/pngmem.c \
lib/libpng/pngpread.c \
lib/libpng/pngread.c \
lib/libpng/pngrio.c \
lib/libpng/pngrtran.c \
lib/libpng/pngrutil.c \
lib/libpng/pngset.c \
lib/libpng/pngtrans.c \
lib/libpng/pngwio.c \
lib/libpng/pngwrite.c \
lib/libpng/pngwtran.c \
lib/libpng/pngwutil.c 

SRC := \
mainwindows.c \
texture.c \
global.c \
shader.c \
winfont.c \
geometry.c

CC = gcc
ALL =$(ZLIB) $(LIBPNG) $(SRC)

test : TARGET := test.exe
test : LDFLAGS = -lgdi32 -lglew32 -lopengl32 -lfreetype
test :
	$(CC) $(CFLAGS) -o $(TARGET) -g $(ALL) $(LDFLAGS)
clean : 
	-rm -f test.exe