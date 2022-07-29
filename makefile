install:
	@echo Installation in progress. Please wait
	@gcc sdcopy.c -g0 -O0 -o /bin/sdcopy
	@chmod ugo+rx /bin/sdcopy
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/sdcopy
	@echo Uninstallation was successfuly complete