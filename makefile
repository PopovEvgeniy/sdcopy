install:
	@echo Installation in progress. Please wait
	@gcc sdcopy.c -g0 -O0 -o /bin/sdcopy
	@chmod ugo+rx /bin/sdcopy
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/sdcopy
	@echo Uninstallation successfully complete