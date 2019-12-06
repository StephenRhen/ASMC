

SUBDIRS = src examples

$(MAKECMDGOALS): subdirs

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

# Make sure the compiler gets built first
examples: src

clean:
	rm -f *~

.PHONY: $(MAKECMDGOALS) $(SUBDIRS) subdirs clean
