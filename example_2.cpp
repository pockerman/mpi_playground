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
	
	MPI_Status status;
	if(rank == 0){
	
		std::cout<<"Hello from process "<<rank<<" of "<<n_procs<<std::endl;
		int num = 2;
		
		// send a number to the worker 
		MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		
		// recv the answer
		int ans = -1;
		MPI_Recv(&ans, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		
		if(ans == 0){
			std::cout<<"Number "<<num<<" is odd"<<std::endl;		
		}
		else{
		
			std::cout<<"Number "<<num<<" is even"<<std::endl;
		}
		
	}
	else if(rank == 1){
	
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
	
	}
	
	
	
	MPI_Finalize();
	// No MPI calls beyond this point
	
	return 0;

}
