# Prueba mpi

#variable compilador
CC=g++
#optimizaciones
#CFLAGS=-DDEBUG -O3 #-D (pasar variables) -O[0,1,2,3](optimizacion)
CFLAGS=-g -DDEBUG -std=c++11
LDLIBS=
INCLUDE=-I. -I./include
EXEC=run
OBJS=main.o terminal.o node.o tree.o command.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(LDLIBS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
