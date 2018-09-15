all:
	cd src
	$(MAKE) -f Makefile.mak
	cd ..

clean:
	cd src
	$(MAKE) -f Makefile.mak clean
	cd ..
