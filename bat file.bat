@echo on

g++ -m64 -Wall -O2 -std=c++17 -c main.cpp
g++ -m64 -Wall -O2 -std=c++17 -c sorter.cpp
g++ -m64 -Wall -O2 -std=c++17 -c logger.cpp
g++ -m64 -Wall -O2 -std=c++17 main.o sorter.o logger.o -o basic_algorithm_program

pause
exit