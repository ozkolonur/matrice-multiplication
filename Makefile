
MPI_CFLAGS = $(shell mpicc --showme:compile)
MPI_LDFLAGS = $(shell mpicc --showme:link)

mpi: mpi.c
	gcc mpi.c $(MPI_CFLAGS) $(MPI_LDFLAGS) -o mpi

standart:
	gcc standart.c -o standart

clean:
	rm -f main standart
