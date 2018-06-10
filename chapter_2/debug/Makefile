OBJS=*.o
ALL_OBJS = $(ROOT_DIR)/$(OBJS_DIR)/$(OBJS)

all: clean $(ROOT_DIR)/$(BIN_DIR)/$(BIN)
clean:
	@rm -rf $(ROOT_DIR)/$(BIN_DIR)/$(BIN)

$(ROOT_DIR)/$(BIN_DIR)/$(BIN):
	$(CC) -o $@ $(ALL_OBJS) $(LDFLAGS)

#	$(CC) -o $@ /home/jason/github/The_C_Programming_Language/chapter_1/src/exercise/exercise_1_19.o $(LDFLAGS)
#$(ROOT_DIR)/$(LIB_DIR)/lib${BIN}.a:
#	ar -cr $@ $(ROOT_DIR)/$(OBJS_DIR)/$(OBJS)

#$(ROOT_DIR)/$(LIB_DIR)/lib${BIN}.so:$(ALL_SOURCE)
#	$(CC) -shared -fPIC -o $@ $^ $(CFLAGS)
