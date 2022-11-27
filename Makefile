CSI := \x1b[

CC := clang
SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)
EXECS := $(SOURCES:%.c=%)

.PHONY: all
#all: $(OBJECTS) $(EXECS)
all: ListFun MapFun CollectionFun BitSetFun StringFun

ListFun: ListFun.o Lists.o Map.o Collection.o String.o BitSet.o Types.o KeyValue.o
	@$(CC) -o $@ $^
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65H$@ compiled$(CSI)0m$(CSI)u"

MapFun: MapFun.o Lists.o Map.o Collection.o String.o Types.o KeyValue.o
	@$(CC) -o $@ $^
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65H$@ compiled$(CSI)0m$(CSI)u"

CollectionFun: CollectionFun.o Lists.o Map.o Collection.o String.o Types.o KeyValue.o
	@$(CC) -o $@ $^
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65H$@ compiled$(CSI)0m$(CSI)u"

BitSetFun: BitSetFun.o BitSet.o
	@$(CC) -o $@ $^
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65H$@ compiled$(CSI)0m$(CSI)u"

StringFun: StringFun.o String.o Collection.o Types.o Lists.o
	@$(CC) -o $@ $^
	@printf "$(CSI)s$(CSI)0;40H$(CSI)32;40m$(CSI)0K$(CSI)0;65H$@ compiled$(CSI)0m$(CSI)u"


.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(CSI)s$(CSI)0;50H$(CSI)47m$(CSI)0K$(CSI)0m$(CSI)0;40H$(CSI)1mCompiling:$(CSI)0;30;47m${@}$(CSI)0m$(CSI)u"

.o.:
	@$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	-@ rm *.o 
	-@ rm ListFun MapFun CollectionFun BitSetFun StringFun