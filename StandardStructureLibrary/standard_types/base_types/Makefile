#get the child directory file
SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')

#get all c file
CUR_SOURCE=${wildcard *.c}

#header file
HEADER_PATH := -I./

#replace all cfile to o file
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}

all:$(SUBDIRS) $(CUR_OBJS)

$(SUBDIRS):ECHO
	make -C $@
$(CUR_OBJS):%.o:%.c
	$(CC) -c $^ $(HEADER_PATH) $(CFALG) -o $(ROOT_DIR)/$(OBJS_DIR)/$@
ECHO:
	@echo $(SUBDIRS)