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

COMMON_SRC := \
texture.c \
global.c \
shader.c \
geometry.c

CC ?= cc
ALL = $(ZLIB) $(LIBPNG) $(COMMON_SRC)

ifeq ($(shell uname -s),Darwin)
TARGET := jk2d
MAC_APP := JK2D.app
CFLAGS := -Wall -DGL_SILENCE_DEPRECATION $(shell pkg-config --cflags libpng zlib)
ALL := $(COMMON_SRC)
LDFLAGS := $(shell pkg-config --libs libpng zlib)

$(TARGET): mainmac.m $(ALL)
	$(CC) $(CFLAGS) -g -o $@ mainmac.m $(ALL) $(LDFLAGS) -framework Cocoa -framework OpenGL

app: $(TARGET)
	mkdir -p $(MAC_APP)/Contents/MacOS $(MAC_APP)/Contents/Resources
	cp $(TARGET) $(MAC_APP)/Contents/MacOS/$(TARGET)
	cp bg_day.png test2.png $(MAC_APP)/Contents/Resources/
	cp macos/Info.plist $(MAC_APP)/Contents/Info.plist

test: $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf $(MAC_APP)
else
test : TARGET := test.exe
test : LDFLAGS = -lgdi32 -lglew32 -lopengl32 -lfreetype
test :
	$(CC) $(CFLAGS) -o $(TARGET) -g $(ALL) mainwindows.c winfont.c $(LDFLAGS)
clean : 
	-rm -f test.exe
endif
