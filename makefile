all: ini.o shareacc.o switch.o
	g++ -o shareacc shareacc.o ini.o
	g++ -o switch switch.o ini.o -lcgicc

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

ini.o: ini.cpp ini.h
	g++ -c ini.cpp

shareacc.o: shareacc.cpp ini.h
	g++ -c shareacc.cpp

switch.o: switch.cpp ini.h
	g++ -c switch.cpp

clean:
	rm ini.o shareacc.o switch.o
