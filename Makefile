CC = cc
INCLUDE = .
CFLAGS = -Wall -O3
DEFINES = -DSC_ALWAYSINLINE=1
OBJECTS = 
TARGET = demo.bin

demo: $(OBJECTS)
	$(CC) -I$(INCLUDE) $(CFLAGS) $(DEFINES) $(OBJECTS) demo.c -o $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o *.bin *.s
