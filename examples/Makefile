

SUBDIRS = Led1 Led2 Blink1 Blink2 Blink3

$(MAKECMDGOALS): subdirs

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

clean:
	rm -f *~

.PHONY: $(MAKECMDGOALS) $(SUBDIRS) subdirs clean
