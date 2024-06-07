<h1 align="center">Multilevel Queue Scheduler</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C-Programming-blue.svg">
  <img src="https://img.shields.io/badge/Scheduling-Algorithms-brightgreen.svg">
  <img src="https://img.shields.io/badge/License-MIT-green.svg">
</p>

This repository contains a C implementation of a Multilevel Queue Scheduler. This scheduler uses four different queues with different scheduling algorithms to manage processes based on their priority levels.

<h1>📖 Description</h1>

The Multilevel Queue Scheduler organizes processes into four separate queues, each with a different scheduling algorithm:
- **Queue 0**: Round Robin (RR) Scheduling
- **Queue 1**: Shortest Job First (SJF) Scheduling
- **Queue 2**: Shortest Job First (SJF) Scheduling
- **Queue 3**: First Come First Serve (FCFS) Scheduling

Each queue has a different priority, with Queue 0 being the highest priority and Queue 3 being the lowest.

<h1>🛠️ Implementation Details</h1>

The scheduler is implemented in C and uses structures and functions to manage processes and their execution. Here's an overview of the main components:

### Structures

```c
typedef struct process{
    int process_id;
    int burst_time;
    int remaining_burst_time;
    int priority;
} process;
```

### Queues

```c
process queue0[MaxProcesses];
process queue1[MaxProcesses];
process queue2[MaxProcesses];
process queue3[MaxProcesses];
```

### Scheduling Algorithms

- **Round Robin (RR)**: Implemented for `queue0`.
- **Shortest Job First (SJF)**: Implemented for `queue1` and `queue2`.
- **First Come First Serve (FCFS)**: Implemented for `queue3`.

### Key Functions

```c
void enqueue(process *queue, int *size, process newprocess);
process dequeue(process *queue, int *size);
void RR_Scheduling(process *queue, int *size);
void SJF_Scheduling(process *queue, int *size);
void FCFS_Scheduling(process *queue, int *size);
void Multilevel_Queue_Scheduler();
```

<h1>🚀 Usage</h1>

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/multilevel-queue-scheduler.git
   cd multilevel-queue-scheduler
   ```

2. **Compile the program:**
   ```bash
   gcc multilevel_queue_scheduler.c -o scheduler
   ```

3. **Run the executable:**
   ```bash
   ./scheduler
   ```

4. **Follow the prompts to enter the number of processes, their priorities, and burst times.**

<h1>📝 Example</h1>

```
****MULTILEVEL QUEUE SCHEDULER****
Enter the number of processes : 3
Process ID : 1
   Enter Priority (0=Highest Priority , 1=Second Highest Priority , 2=Third Highest Priority , 3= Lowest Priority) : 0
   Enter Burst Time : 5
Process ID : 2
   Enter Priority (0=Highest Priority , 1=Second Highest Priority , 2=Third Highest Priority , 3= Lowest Priority) : 1
   Enter Burst Time : 3
Process ID : 3
   Enter Priority (0=Highest Priority , 1=Second Highest Priority , 2=Third Highest Priority , 3= Lowest Priority) : 3
   Enter Burst Time : 7

Queue 0 is executing with RR
Process with Pid : 1 is started executing with 5 Burst Time 
Process with Pid : 1 's Execution is completed 100%. 

Queue 1 is executing with SJF
Process with Pid : 2 is started executing with 3 Burst Time 
Process with Pid : 2 's Execution is completed 100%. 

Queue 3 is executing with FCFS
Process with Pid : 3 is started executing with 7 Burst Time 
Process with Pid : 3 's Execution is completed 100%. 

All Processes are executed successfully!
Total Time taken by CPU to execute all the processes : 15
