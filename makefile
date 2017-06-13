install:
	@echo Compiling the program source code. Please wait
	@gcc sdcopy.c -g0 -O0 -o sdcopy
	@echo Compilation successfuly complete
	@chmod ugo+rx sdcopy
	@echo Enter you user password for do last installation step
	@sudo cp -f -p sdcopy /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/sdcopy
	@echo Uninstallation complete