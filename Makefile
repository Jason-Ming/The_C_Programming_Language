#子目录的Makefile直接读取其子目录就行
SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "include")print $$9}')

all:$(SUBDIRS)

$(SUBDIRS):ECHO
	make -C $@

ECHO:
	@echo $(SUBDIRS)

ALL_D = $(shell find -type f -name '*.d')
ALL_D_TEMP = $(shell find -type f -name '*.d.*')
ALL_O = $(shell find -type f -name '*.o')
ALL_TXT = $(shell find -type f -name '*.txt')
ALL_I = $(shell find -type f -name '*.i')
ALL_SO = $(shell find -type f -name '*.so')
ALL_A = $(shell find -type f -name '*.a')
ALL_OUT = $(shell find -type f -name '*.out')

clean:
	@rm -rf $(ALL_D)
	@rm -rf $(ALL_D_TEMP)
	@rm -rf $(ALL_TXT)
	@rm -rf $(ALL_O)
	@rm -rf $(ALL_I)
	@rm -rf $(ALL_SO)
	@rm -rf $(ALL_A)
	@rm -rf $(ALL_OUT)