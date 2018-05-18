LIB_PATH=$(HOME)/github/stupid_lib

CC      := gcc
#CFLAGS  += -M
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
LDFLAGS += -L$(LIB_PATH)/debug/lib -Wl,-rpath $(LIB_PATH)/debug/lib -lstupid


TARGET = 1_1.bin 1_2.bin 1_3.bin 1_4.bin 1_5_1.bin 1_5_2.bin 1_5_3.bin 1_5_4.bin 1_6.bin 1_7.bin  1_8.bin 1_9.bin
all: $(TARGET)

%.bin: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.d:%.c
	@set -e; rm -f $@; $(CC) -MM $< $(INCLUDEFLAGS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf $(TARGET) *.o

