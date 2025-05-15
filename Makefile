CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0 json-c libcurl`
LDFLAGS = `pkg-config --libs gtk+-3.0 json-c libcurl`
TARGET = weather-app

all: $(TARGET)

$(TARGET): xnew.c
	$(CC) $(CFLAGS) -o $(TARGET) xnew.c $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
