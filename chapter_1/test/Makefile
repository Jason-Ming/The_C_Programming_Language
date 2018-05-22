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



# ����Լ����ӳ���source.c֮����ļ������������source.o ֮��׷���������ļ�������������util.c��������util.o���ɣ������Ĳ���Ҫ�Ķ�
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