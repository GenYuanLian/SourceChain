.PHONY: FORCE
all: FORCE
	$(MAKE) -C .. srcchain_qt test_srcchain_qt
clean: FORCE
	$(MAKE) -C .. srcchain_qt_clean test_srcchain_qt_clean
check: FORCE
	$(MAKE) -C .. test_srcchain_qt_check
srcchain-qt srcchain-qt.exe: FORCE
	 $(MAKE) -C .. srcchain_qt
