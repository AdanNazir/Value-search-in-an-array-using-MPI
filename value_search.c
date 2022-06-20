#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv)
{
    int rank=-1;
    int np;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    //printf("Hello from %d\n",rank);

    if (rank == 0 && np>1)
    {
	int rec_signal=0;
    int iter=0;
    int num=1;
    int k=0;
    int* buf = (int*)malloc(sizeof(int) *(np*10));
    printf("Process %d has data: ",rank);
    for(int i=0;i<np*10;i++){
    	buf[i]=num;
    	printf("%d",buf[i]);
    	printf(" ");
    	num+=2;
    	}
    	printf("\n");
    	int temp=39;
    	printf("The number to search is %d",temp);
    	printf("\n");
    	for (int j=0;j<np-1;j++){
    	int *send_buf=(int*)malloc(sizeof(int) *10);
    
	for (int k=0;k<10;k++){
	send_buf[k]=buf[iter];
    	iter+=1;
    	}
    	
    	MPI_Send(send_buf,10, MPI_INT,j+1, 0, MPI_COMM_WORLD);
    
    MPI_Send(&temp,1, MPI_INT,j+1, 0, MPI_COMM_WORLD);
    MPI_Recv(&rec_signal,1,MPI_INT,j+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    int new_sig=rec_signal;
    if (new_sig==1){
    printf("Master: Process %d has found the number:!",j+1);
    printf("\n");
    printf("Master: Informing all processes to abort!");
    for (int itr=0;itr<np-1;itr++){
    MPI_Send(&new_sig,1, MPI_INT,itr+1, 0, MPI_COMM_WORLD);
    	}
    	
    	}
    	}
    	}
    
    else{
    int* str_buf = (int*)malloc(sizeof(int) *10);  
    int num_find=0;
    MPI_Recv(str_buf,10,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    	printf("Process %d has local data : ",rank);
    	for (int i=0;i<10;i++){
    		printf("%d",str_buf[i]);
    		printf(" ");
    }
    printf("\n");
    MPI_Recv(&num_find,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    int signal=0;
    	for (int i=0;i<10;i++){
    		if (str_buf[i]==num_find){
    			printf("Process %d: I have found the number:)",rank);
    			printf("\n");
    			signal=1;
    			MPI_Send(&signal,1, MPI_INT,0, 0, MPI_COMM_WORLD);
    			MPI_Finalize();
    			return 0;
    }
    }
    
    MPI_Send(&signal,1,MPI_INT,0,0,MPI_COMM_WORLD);
    MPI_Recv(&signal,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Process %d: Abort search!",rank);
   MPI_Finalize();
    return 0;
    }
    }
    	
