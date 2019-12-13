

SUBDIRS = ex01_Led1 ex02_Led2 ex03_Blink1 ex04_Blink2 \
          ex05_Blink3

$(MAKECMDGOALS): subdirs

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

clean:
	rm -f *~

.PHONY: $(MAKECMDGOALS) $(SUBDIRS) subdirs clean
