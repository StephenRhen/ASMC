SUBDIRS = tutorial

$(MAKECMDGOALS): subdirs

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

clean:
	rm -f *~

.PHONY: $(MAKECMDGOALS) $(SUBDIRS) subdirs clean
