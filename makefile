install:
	@echo Installation in progress. Please wait
	@$(CC) sdcopy.c -g0 -O0 -o /bin/sdcopy
	@chmod ugo+rx /bin/sdcopy
	@echo Installation was successfully completed
uninstall:
	@rm -f /bin/sdcopy
	@echo Uninstallation was successfully completed