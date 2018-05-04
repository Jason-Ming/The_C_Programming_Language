LIB_PATH=$(HOME)/github/stupid_lib

CC      := gcc
CFLAGS  += -g -Wall
CFLAGS  += -std=c99
#CFLAGS  += -D CPPUTEST
#CFLAGS  += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
CFLAGS   += -I$(LIB_PATH)/include

CPP     := g++
CPPFLAGS  += -g -Wall
#CPPFLAGS  += -I$(CPPUTEST_HOME)/include
#CPPFLAGS works for both .c and .cpp files!

#CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h

#LDFLAGS := -L$(CPPUTEST_HOME)/lib -lCppUTest
LDFLAGS += -L$(LIB_PATH)/lib -Wl,-rpath $(LIB_PATH)/lib -lstupid

TARGET = exercise_1_1.bin exercise_1_2.bin exercise_1_3.bin exercise_1_4.bin exercise_1_5.bin exercise_1_6.bin exercise_1_7.bin
TARGET += exercise_1_8.bin exercise_1_9.bin exercise_1_10.bin exercise_1_11.bin exercise_1_12.bin exercise_1_13.bin exercise_1_14.bin
TARGET += exercise_1_15.bin exercise_1_16.bin exercise_1_17.bin exercise_1_18.bin exercise_1_19.bin

all: $(TARGET)

%.bin: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf $(TARGET) *.o




