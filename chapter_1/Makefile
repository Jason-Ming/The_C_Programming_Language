CPPUTEST_HOME = /usr

CC      := gcc
CFLAGS    += -g -Wall
CFLAGS  += -std=c99
CFLAGS  += -D CPPUTEST
CFLAGS  += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

CPP     := g++
CPPFLAGS  += -g -Wall
CPPFLAGS  += -I$(CPPUTEST_HOME)/include
#CPPFLAGS works for both .c and .cpp files!

CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h

LDFLAGS := -L$(CPPUTEST_HOME)/lib -lCppUTest



# 如果自己增加除了source.c之外的文件，请在下面的source.o 之后追加新增的文件，例如新增了util.c，则添加util.o即可，其他的不需要改动
objects:= AllTests.o TestCases.o 1_5_4.o

test: $(objects)
	$(CPP) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS) $(MEMFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(MEMFLAGS)

.PHONY: clean
clean:
	@echo "clean..."
	rm -rf test *.o
