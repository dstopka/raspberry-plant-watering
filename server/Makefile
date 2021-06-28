CC = gcc
GENERIC_FLAGS = -Wall -Wextra
CFLAGS = $(GENERIC_FLAGS) -O0 -MMD -MP

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG
endif

LINKER = gcc
LFLAGS = $(GENERIC_FLAGS) -lwiringPi -lpthread

TARGET := server
PROJECT_ROOT = ..
COMMON_DIR = $(PROJECT_ROOT)/common
BIN_DIR := bin
SRC_DIR := src
LIB_DIR := lib
INC_DIR := include

LIBS = 	$(COMMON_DIR)/request \
		$(COMMON_DIR)/response \
		$(COMMON_DIR)/valve_state \
		$(COMMON_DIR)/trace
LIBS_SRCS = $(shell find $(LIBS) -name *.c)
LIBS_OBJS = $(addprefix $(LIB_DIR)/, $(notdir $(LIBS_SRCS:.c=.o)))
INC_FILES = $(shell find $(LIBS) -name *.h)
SRCS = $(shell find $(SRC_DIR) -name *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS += $(filter-out $(SRC_DIR),$(shell find $(SRC_DIR) -type d)) $(INC_DIR)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

VPATH = $(sort $(LIBS))

.PHONY: all libs clean hello

all: libs $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS) $(LIBS_OBJS)
	@mkdir -p $(BIN_DIR)
	$(LINKER) $(LFLAGS) $(OBJS) $(LIBS_OBJS) -o $@
	@echo "Finished building " $@ "successfully\n"

$(OBJS): %.o : %.c 
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@
	@echo -e "Compiled "$<" successfully to "$@"\n"

$(LIBS_OBJS): lib
$(LIB_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@
	@echo -e "Compiled "$<" successfully to "$@"\n" 

libs:
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(INC_DIR)
	@cp -r $(INC_FILES) $(INC_DIR)

clean: 
	rm -f $(OBJS) $(DEPS)
	rm -rf $(BIN_DIR)
	rm -rf $(LIB_DIR)
	rm -rf $(INC_DIR)

-include $(DEPS)