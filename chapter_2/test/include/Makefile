#子目录的Makefile直接读取其子目录就行
SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')
CUR_DIR=$(shell pwd)
#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.cpp}
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}

all:$(SUBDIRS) $(CUR_OBJS)

$(SUBDIRS):ECHO
	make -C $@

$(CUR_OBJS):%.o:%.cpp
	$(CPP) -o $@ -c $< $(CPPFLAGS) $(CXXFLAGS)
	@cp $@ $(ROOT_DIR)/test/$(OBJS_DIR)/$@

%.d:%.cpp
	@set -e; rm -f $@; $(CPP) -MM $< $(INCLUDEFLAGS) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(CUR_OBJS:.o=.d)

ECHO:
	@echo $(SUBDIRS)

