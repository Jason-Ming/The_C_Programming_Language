LIB_PATH=$(HOME)/github/stupid_lib

CC      := gcc
#CFLAGS  += -M
CFLAGS  += -g -Wall
CFLAGS  += -std=c99
#CFLAGS  += -D CPPUTEST
#CFLAGS  += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
CFLAGS   += -I$(LIB_PATH)/include
INCLUDEFLAGS = -I$(LIB_PATH)/include

CPP     := g++
CPPFLAGS  += -g -Wall
#CPPFLAGS  += -I$(CPPUTEST_HOME)/include
#CPPFLAGS works for both .c and .cpp files!

#CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h

#LDFLAGS := -L$(CPPUTEST_HOME)/lib -lCppUTest
LDFLAGS += -L$(LIB_PATH)/debug/lib -Wl,-rpath $(LIB_PATH)/debug/lib -lstupid

TARGET = exercise_1_1.bin exercise_1_2.bin exercise_1_3.bin exercise_1_4.bin exercise_1_5.bin exercise_1_6.bin exercise_1_7.bin
TARGET += exercise_1_8.bin exercise_1_9.bin exercise_1_10.bin exercise_1_11.bin exercise_1_12.bin exercise_1_13.bin exercise_1_14.bin
TARGET += exercise_1_15.bin exercise_1_16.bin exercise_1_17.bin exercise_1_18.bin exercise_1_19.bin exercise_1_22.bin
TARGET += 1_1.bin 1_2.bin 1_3.bin 1_4.bin 1_5_1.bin 1_5_2.bin 1_5_3.bin 1_5_4.bin 1_6.bin 1_7.bin  1_8.bin 1_9.bin

CUR_SOURCE=${wildcard *.c}
#将对应的c文件名转为o文件后放在下面的CUR_OBJS变量中
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}

all: $(TARGET)

%.bin: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.d:%.c
	@set -e; rm -f $@; $(CC) -MM $< $(INCLUDEFLAGS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(CUR_OBJS:.o=.d)

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf $(TARGET) *.o *.d *.i




