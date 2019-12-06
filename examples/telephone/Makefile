

all: telephone.fsm.c

telephone.fsm.c: telephone.fsm
	../../src/asmc -tf telephone.tf $^

.PHONY: clean
clean:
	rm -f telephone.fsm.c telephone.fsm.h telephone.tf
