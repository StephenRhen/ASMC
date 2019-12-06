

YACC = bison
LEX = flex
CC = gcc

YFLAGS += -d
CFLAGS += -g

# Replace brain dead builtin rule
%.tab.c %.tab.h: %.y
	$(YACC) $(YFLAGS) $<

C_SRCS = asmc.c sm.c gen_cpp.c lexer.c parser.tab.c
C_OBJS = $(patsubst %.c, %.o, $(C_SRCS))

all:  asmc

asmc: $(C_OBJS)

lexer.c: parser.tab.h

.PHONY: clean
clean:
	rm -f asmc $(C_OBJS) lexer.c parser.tab.c parser.tab.h *~

