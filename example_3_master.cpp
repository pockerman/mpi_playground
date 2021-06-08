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
	
	std::cout<<"Hello from master process..."<<std::endl;
	std::cout<<"Number of workers..."<<n_procs-1<<std::endl;
	
	
	int stop = 0;
	
	while(stop == 0){
	
		int num = 0;
		std::cout<<"Enter a number..."<<std::endl;
		std::cin>>num;
	

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
		
		std::cout<<"Stop? (press 1 for yes)..."<<std::endl;
		std::cin>>stop;
		
		MPI_Send(&stop, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		
	}
	
	
	MPI_Finalize();
	// No MPI calls beyond this point
	
	return 0;
}
