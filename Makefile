# Release/Debug
DEBUG=no

# Directories
SRC_DIR = SRC
OBJ_DIR = OBJ
INC_DIR = SRC
BIN_DIR = BIN

# Compilation flags
CXX = gcc
CXXFLAGS = -Wall -lglut -lGLU -lopenal -lGL -lm
LDFLAGS = 
ifeq ($(DEBUG), yes)
	CXXFLAGS += -g -DDEBUG
else
	CXXFLAGS += -O2 -s -Wno-unused-result
endif

# Sources & Headers & Bin
SRC = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJ = $(addsuffix .o, $(basename $(subst ${SRC_DIR}, ${OBJ_DIR}, ${SRC})))
BIN = prog

# Make
.PHONY: clean mrproper

.SUFFIXES:

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o ${BIN_DIR}/${BIN} $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

test_dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(INC_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	@rm -f $(OBJ)

mrproper: clean
	@rm -rf $(BIN_DIR)/$(BIN)
	@rm -rf $(BIN_DIR)/*.cfg

rebuild: mrproper all