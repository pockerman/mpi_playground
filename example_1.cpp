#include <mpi.h>
#include <iostream>
int main(int argc, char** argv){

	int rank;
	int n_procs;
	
	// initialize MPI. No MPI calls
	// prior to this point should be made
	MPI_Init(&argc, &argv);
	
	// what's my rank
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// how may procs
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
	
	std::cout<<"Hello from process "<<rank<<" of "<<n_procs<<std::endl;
	
	MPI_Finalize();
	// No MPI calls beyond this point


}
