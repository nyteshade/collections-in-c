CSI := \x1b[

SRC := src
BIN := bin
OBJ := obj
LIB := lib
EXM := examples

CC := clang
CFLAGS := -Iinclude
SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)
EXECS := $(SOURCES:%.c=%)

.PHONY: all
#all: $(OBJECTS) $(EXECS)
all: NEListFun NEMapFun NECollectionFun NEBitSetFun NEStringFun libnecollections.a

NEListFun NEMapFun NECollectionFun NEBitSetFun NEStringFun: $(OBJECTS) | $(BIN)
	@$(CC) $(CFLAGS) -o $(BIN)/$@ $(EXM)/$@.c $^
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65H$@ compiled$(CSI)0m$(CSI)u"

libnecollections.a: $(OBJECTS) | $(LIB)
	@printf "Creating library...\n"
	@mkdir >/dev/null 2>/dev/null -p $(LIB) $(LIB)/include/NECollections
	@zsh -o extended_glob -c 'ar -cvq $(LIB)/libnecollections.a $(OBJ)/*.o~*Fun.o'
	@cp -rp include/NECollections/*.h $(LIB)/include/NECollections
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65Hlibnecollections.a created$(CSI)0m$(CSI)u"

$(OBJ) $(BIN) $(LIB):
	mkdir -p ${@}

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(CSI)s$(CSI)0;50H$(CSI)47m$(CSI)0K$(CSI)0m$(CSI)0;40H$(CSI)1mCompiling:$(CSI)0;30;47m${@}$(CSI)0m$(CSI)u"

.PHONY: clean
clean:
	-@ rm -rf $(BIN) $(LIB) $(OBJ)
