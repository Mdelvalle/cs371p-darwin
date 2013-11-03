all:
	make Darwin.zip

clean:
	rm -f Darwin.log
	rm -f Darwin.zip
	rm -f RunDarwin
	rm -f RunDarwin.out

doc: Darwin.h
	doxygen Doxyfile

turnin-list:
	turnin --list reza cs371ppj4

turnin-submit: Darwin.zip
	turnin --submit reza cs371ppj4 Darwin.zip

turnin-verify:
	turnin --verify reza cs371ppj4

Darwin.log:
	git log > Darwin.log

Darwin.zip: makefile                          \
               Darwin.c++ Darwin.h Darwin.log \
               Darwin.pdf                     \
               RunDarwin.c++ RunDarwin.out    \
               TestDarwin.c++ TestDarwin.out
	zip -r Darwin.zip                     \
	       html/ makefile                 \
           Darwin.c++ Darwin.h Darwin.log \
           Darwin.pdf                     \
           RunDarwin.c++ RunDarwin.out    \
           TestDarwin.c++ TestDarwin.out

RunDarwin: Darwin.h Darwin.c++ RunDarwin.c++
	g++ -pedantic -std=c++0x -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin -lgtest -lpthread -lgtest_main

RunDarwin.out: RunDarwin
	valgrind RunDarwin > RunDarwin.out

TestDarwin: Darwin.h Darwin.c++ TestDarwin.c++
	g++ -pedantic -std=c++0x -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lpthread -lgtest_main

TestDarwin.out: TestDarwin
	valgrind TestDarwin > TestDarwin.out
