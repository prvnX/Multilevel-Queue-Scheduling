#include <stdio.h>
#define MaxProcesses 250
typedef struct process{
    int process_id;
    int burst_time;
    int remaining_burst_time;
    int priority;
}process;
process queue0[MaxProcesses]; //highest priority queue with RR Scheduling
process queue1[MaxProcesses]; //2nd highest priority queue with SJF Scheduling
process queue2[MaxProcesses]; //3rd highest priority queue with SJF Scheduling
process queue3[MaxProcesses]; //lowest priority queue with FCFS Scheduling
int size_queue0=0;
int size_queue1=0;
int size_queue2=0;
int size_queue3=0; //sizes of queues
const int time_quantum=4; //time quantum is 4 units for RR
int total_time=0; //total unit of time that cpu takes to execute all processes
const int switch_time=20; // Time taken by the CPU to switch between processes within a single queue round 

void enqueue(process *queue,int *size,process newprocess){
    queue[*size]=newprocess;
    (*size)++;
}

process dequeue(process *queue,int *size){
    process temp_process=queue[0];
    (*size)--;
    for(int i=0;i<(*size);i++){
        queue[i]=queue[i+1];
    }
    return temp_process;
}
//Round Robin(RR) Scheduling Algorithm
void RR_Scheduling(process *queue,int *size){
    int switchtime=switch_time;
    while(switchtime>0 && *size > 0){
        if(switchtime>=time_quantum){
            process exe_process=dequeue(queue,size);
            printf("Process with Pid : %d is started executing with %d Burst Time \n",exe_process.process_id,exe_process.remaining_burst_time);
            if(exe_process.remaining_burst_time>=time_quantum){
                switchtime=switchtime-time_quantum;
                exe_process.remaining_burst_time=exe_process.remaining_burst_time - time_quantum;
                if(exe_process.remaining_burst_time==0){
                    printf("Process with Pid : %d 's Execution is completed 100%%. \n\t*******\t\n",exe_process.process_id);
                }
                else{
                    enqueue(queue,size,exe_process);
                    float percentage = ((float)(exe_process.burst_time - exe_process.remaining_burst_time) / exe_process.burst_time)*100.0;
                    printf("Process with Pid : %d | %.2f %% of Execution completed | Remaining Burst time : %d\n",exe_process.process_id,percentage,exe_process.remaining_burst_time);
                }
                total_time=total_time + time_quantum;
            }
            else{
                switchtime=switchtime-exe_process.remaining_burst_time;
                total_time=total_time + exe_process.remaining_burst_time;
                exe_process.remaining_burst_time = 0;
                printf("Process with Pid : %d 's Execution is completed 100%%. \n\t*******\t\n",exe_process.process_id);
            
             }
        }
        else{
            if(queue[0].remaining_burst_time<=switchtime){
                printf("Process with Pid : %d is started executing with %d Burst Time \n",queue[0].process_id,queue[0].remaining_burst_time);
                switchtime=switchtime-queue[0].remaining_burst_time;
                total_time=total_time+queue[0].remaining_burst_time;
                queue[0].remaining_burst_time=0;
                process exe_process=dequeue(queue,size);
                printf("Process with Pid : %d 's Execution is completed 100%%. \n\t*******\t\n",exe_process.process_id);
            }
            else{
                queue[0].remaining_burst_time=queue[0].remaining_burst_time-switchtime;
                total_time=total_time+switchtime;
                switchtime=0;
                float percentage = ((float)(queue[0].burst_time - queue[0].remaining_burst_time) / queue[0].burst_time)*100.0;
                printf("Process with Pid : %d | %.2f %% of Execution completed | Remaining Burst time : %d\n",queue[0].process_id,percentage,queue[0].remaining_burst_time);
            }
        }
    }
}
//Shortest Job First (SJF) Scheduling Algorithm
void SJF_Scheduling(process *queue,int *size){
    int switchtime=switch_time;
    while(switchtime>0 && *size>0){
        int shortest_job=0;
        for(int i=0;i<*size;i++){
            if(queue[i].remaining_burst_time < queue[shortest_job].remaining_burst_time){
                shortest_job=i;
            }
        }
        process exe_process = dequeue((queue+shortest_job),size);
        printf("Process with Pid : %d is started executing with %d Burst Time\n",exe_process.process_id,exe_process.remaining_burst_time);
        if(exe_process.remaining_burst_time>=switchtime){
            exe_process.remaining_burst_time=exe_process.remaining_burst_time-switchtime;
            total_time=total_time + switchtime;
            switchtime=0;
            if(exe_process.remaining_burst_time==0){
                printf("Process with Pid : %d 's Execution is completed 100%%. \n\t*******\t\n",exe_process.process_id);
            }
            else{
                enqueue(queue,size,exe_process);
                float percentage = ((float)(exe_process.burst_time - exe_process.remaining_burst_time) / exe_process.burst_time)*100.0;
                printf("Process with Pid : %d  | %.2f %% of Execution completed | Remaining Burst time : %d\n",exe_process.process_id,percentage,exe_process.remaining_burst_time);
            }
        }
        else{
            switchtime=switchtime-exe_process.remaining_burst_time;
            total_time=total_time+exe_process.remaining_burst_time;
            exe_process.remaining_burst_time=0;
            printf("Process with Pid : %d 's Execution is completed 100%%. \n\t*******\t\n");
        }
    }
}
//First Come First Serve (FCFS)(FIFO) Scheduling Algorithm
void FCFS_Scheduling(process *queue,int *size){
    int switchtime=switch_time;
    while(switchtime>0 && *size>0){
         printf("Process with Pid : %d is started executing with %d Burst Time\n",queue[0].process_id,queue[0].remaining_burst_time);
        if(queue[0].remaining_burst_time>switchtime){
            queue[0].remaining_burst_time=queue[0].remaining_burst_time - switchtime;
            total_time=total_time+switchtime;
            switchtime=0;
            float percentage = ((float)(queue[0].burst_time - queue[0].remaining_burst_time) / queue[0].burst_time) * 100.0;
                printf("Process with Pid : %d | %.2f %% of Execution completed | Remaining Burst time : %d\n",queue[0].process_id,percentage,queue[0].remaining_burst_time);

        }
        else{
            switchtime=switchtime - queue[0].remaining_burst_time;
            total_time=total_time+queue[0].remaining_burst_time;
            queue[0].remaining_burst_time=0;
            process exe_process=dequeue(queue,size);
            printf("Process with Pid : %d 's Execution is completed 100%%. \n\t*******\t\n",exe_process.process_id); 
        }
    }
}
//Multilevel Queue Scheduling Algorithm
void Multilevel_Queue_Scheduler(){
    while(size_queue0>0 || size_queue1>0 || size_queue2>0 || size_queue3>0){
        if(size_queue0>0){
            printf("\n\t\t*********\t\t\nQueue 0 is executing with RR\n");
            RR_Scheduling(queue0,&size_queue0);   
        }
        if(size_queue1>0){
            printf("\n\t\t*********\t\t\nQueue 1 is executing with SJF\n");
            SJF_Scheduling(queue1,&size_queue1);         
        }
        if(size_queue2>0){
            printf("\n\t\t*********\t\t\nQueue 2 is executing with SJF\n");
            SJF_Scheduling(queue2,&size_queue2);           
        }
        if(size_queue3>0){
            printf("\n\t\t*********\t\t\nQueue 3 is executing with FCFS\n");
            FCFS_Scheduling(queue3,&size_queue3);            
        }  
    }
    printf("\n\t\t*************************\t\t\nAll Processes are executed successfully !\nTotal Time taken by CPU to execute all the processes : %d\n",total_time);
}

int main(){
    int no_of_processes=0;
    int priority,burst_time;
    printf("\t****MULTILEVEL QUEUE SCHEDULER****\t\nEnter the number of processes : ");
    scanf("%d",&no_of_processes);
    for(int i=1;i<=no_of_processes;i++){
        printf("Process ID : %d\n   Enter Priority (0=Highest Priority , 1=Second Highest Priority , 2=Third Highest Priority , 3= Lowest Priority) : ",i);
        scanf("%d",&priority);
        if(priority>3 || priority<0){
            printf("ERROR!!! Unidentified Priority ,Try Again !\n");
            return 1;
        }
        printf("   Enter Burst Time : ");
        scanf("%d",&burst_time);
        process new_process;
        new_process.process_id=i;
        new_process.priority=priority;
        new_process.burst_time=burst_time;
        new_process.remaining_burst_time=burst_time;
        switch (new_process.priority)
        {
        case 0:
            enqueue(queue0,&size_queue0,new_process);
            break;
        case 1:
            enqueue(queue1,&size_queue1,new_process);
            break;
        case 2:
            enqueue(queue2,&size_queue2,new_process);
            break;
        case 3:
            enqueue(queue3,&size_queue3,new_process);
            break;
        }
    }
    Multilevel_Queue_Scheduler();
    return 0;
}