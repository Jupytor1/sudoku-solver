SRCS	= board_funcs.cpp sudoku_solver.cpp
OBJS	= ${SRCS:.cpp=.o}
HEADER	= header.h
PROGRAM	= solve.exe

all		: ${PROGRAM}

${PROGRAM}	: ${OBJS} ${HEADER}
	g++ -o ${PROGRAM} ${OBJS}

board_funcs.o	: board_funcs.cpp
	g++ -c board_funcs.cpp

sudoku_solver.o	: sudoku_solver.cpp
	g++ -c sudoku_solver.cpp

clean		:
	rm -f *.o

fclean		: clean
	rm -f ${PROGRAM}
