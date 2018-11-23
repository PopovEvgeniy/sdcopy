install:
	@echo Installation in progress. Please wait
	@gcc sdcopy.c -g0 -O0 -o sdcopy
	@chmod ugo+rx sdcopy
	@cp -f -p sdcopy /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/sdcopy
	@echo Uninstallation was successfuly complete