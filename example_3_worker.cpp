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
	
	// needed for receive
	MPI_Status status;
	
	int stop = 0;
	
	while(stop == 0){
	
		// receive 
		int data = -1;
		
		MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		
		if(data % 2 == 0){
			data = 1;
			MPI_Send(&data, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);		
		}
		else{
		
			data = 0;
			MPI_Send(&data, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		
		// check if we must stop
		MPI_Recv(&stop, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
		
		if(stop == 1){
			std::cout<<"Worker "<<rank<<" is shutting down"<<std::endl;
		}
	}
	
	
	MPI_Finalize();
	// No MPI calls beyond this point
	
	return 0;
}
