testdir = ./testdir

test:
	rm -rf $(testdir)
	mkdir $(testdir)
	cp ../*.h $(testdir)
	cp ../*.cpp $(testdir)
	cp Makefile.Tests $(testdir)/Makefile
clean:
	rm -rf $(testdir) 
test001: test
	cp test001.cpp $(testdir)
	cd $(testdir) && make test001

