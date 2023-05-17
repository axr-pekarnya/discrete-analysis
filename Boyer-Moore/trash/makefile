all: main

main: main.o ZFunction.o NFunction.o LFunction.o GoodSuffix.o SymbolTable.o
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm main.o ZFunction.o NFunction.o LFunction.o GoodSuffix.o SymbolTable.o -o main

main.o: main.cpp
	g++ -std=c++14 -w O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c main.cpp

ZFunction.o: ZFunction.cpp
	g++ -std=c++14 -w O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c ZFunction.cpp

NFunction.o: NFunction.cpp
	g++ -std=c++14 -w O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c NFunction.cpp

LFunction.o: LFunction.cpp
	g++ -std=c++14 -w O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c LFunction.cpp

GoodSuffix.o: GoodSuffix.cpp
	g++ -std=c++14 -w O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c GoodSuffix.cpp

SymbolTable.o: SymbolTable.cpp
	g++ -std=c++14 -w O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c SymbolTable.cpp

run:
	./main
clean:
	rm -rf *.o hello
