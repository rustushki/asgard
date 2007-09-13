all:
	g++ -o runquery sqlite3.cpp -lsqlite3
create:
	./runquery asgard.db3 createdb.sql
	./runquery asgard.db3 populatedb.sql
install:
	mv asgard.db3 ../src
clean:
	rm runquery
	rm asgard.db3
