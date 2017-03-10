/*
 * @Author: Ali Raza
 * @Description: Process Scheduling assignment for Operating Systems
 * Include first come first serve and priority scheduling
 */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dyn_array.h"
#include "processing_scheduling.h"
#define QUANTUM 4 // Used for Robin Round for process as the run time limit

// private function
void virtual_cpu(ProcessControlBlock_t *process_control_block) {
    // decrement the burst time of the pcb
    --process_control_block->remaining_burst_time;
}

bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) {

    if(ready_queue == NULL || result == NULL) return false;
    
    ProcessControlBlock_t pcb; 
  
    int capacity = (int)dyn_array_size(ready_queue);
    int burst_time = 0;
    int wall_time = 0;
    int latency = 0;

    for(int i = 0 ; i < capacity; i++){
        latency += burst_time;
        dyn_array_extract_back(ready_queue, (void*)&pcb); //Extract PCB from Dynamic array
        burst_time += pcb.remaining_burst_time;
        wall_time += burst_time;
        while(!pcb.remaining_burst_time){ //decrease remaining burst time after each iteration
            virtual_cpu(&pcb);
        }

    }
    
    //set statistics
    result->average_latency_time = (float)latency/capacity;
    result->average_wall_clock_time = (float)wall_time/capacity;
    result->total_run_time = (float)burst_time;

    return true;
 }

/*
 * Compare the priority of two PCBS
 */
int compare(const void* pcb, const void* pcb2){

    //Compare using nested terenary operator
    return ((ProcessControlBlock_t*)pcb)->priority > ((ProcessControlBlock_t*)pcb2)->priority ? -1
        : ((ProcessControlBlock_t*)pcb)->priority < ((ProcessControlBlock_t*)pcb2)->priority ? 1
        :  0;
}


bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) {
    if(ready_queue == NULL || result == NULL) return false;
    
    int (*const compare_priority)(const void*, const void*) = &compare; //Compare function pointer
    dyn_array_sort(ready_queue, compare_priority); //Sort by priority

    ProcessControlBlock_t pcb;
    //pcb.remaining_burst_time = 0;

    int capacity = (int)dyn_array_size(ready_queue);
    int burst_time = 0;
    int wall_time = 0;
    int latency = 0;

    //printf("\nCapacity = %d\n", capacity);

    for(int i = 0; i < capacity; i++) {
        latency += burst_time;
        dyn_array_extract_back(ready_queue, (void*)&pcb);
        burst_time += pcb.remaining_burst_time;
        wall_time += burst_time;
        while(!pcb.remaining_burst_time) virtual_cpu(&pcb);
    }    

    result->average_latency_time = (float)latency/capacity;
    result->average_wall_clock_time = (float)wall_time/capacity;
    result->total_run_time = burst_time;

    return true;

}

#ifdef GRAD_TESTS
bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) {

    if( ready_queue == NULL || result == NULL) return false;

    //variables for stats
    float total_latency = 0;
    float total_wall_clock = 0;
    float counter = 0;
    //size of the ready queue   
    size_t capacity = dyn_array_size(ready_queue);
        
    ProcessControlBlock_t pcb;
        
    while (!dyn_array_empty(ready_queue)) {
      
        // //End loop if ready_queue is empty
        // if (dyn_array_empty(ready_queue)) 
        //     break;
            
        //Extract head of ready_queue
        dyn_array_extract_back(ready_queue, (void*)&pcb);
            
        //Set started to true and arrival time of process for latency
        if (pcb.started == false) {
            total_latency += counter;
            pcb.started = !pcb.started;
        }
        //decreases the burst time   
        for (uint32_t i = 0; i < quantum; i++) {
            virtual_cpu(&pcb);
            counter++;
            if (pcb.remaining_burst_time == 0) 
                break;
        }
            
        if (pcb.remaining_burst_time == 0) {
            total_wall_clock += counter;
            continue;
        } 
        else {
            //push to front of ready queue
            dyn_array_push_front(ready_queue, &pcb);
        }
    }
        
        //Return totals to result structure
        result->average_latency_time =  total_latency / capacity; //result->average_latency_time =
        result->average_wall_clock_time = total_wall_clock / capacity;
        result->total_run_time = counter;
        return true;
}
#endif

dyn_array_t *load_process_control_blocks(const char *input_file) {
    if(input_file == NULL) return NULL;

    /*
     * Create temporary string to bypass const parameter error
     * Check file extension
     */
    char* temp;
    temp = strrchr(input_file, '.');

    if(temp == NULL || strcmp(temp, ".bin")) return NULL;

    int file_descriptor = open(input_file, O_RDONLY);
    if(file_descriptor <= 0){
        close(file_descriptor);
        return NULL;
    }

    uint32_t length;
    int size = read(file_descriptor, &length, sizeof(uint32_t));
    if(size <= 0) return NULL;

    ProcessControlBlock_t* pcb = malloc(sizeof(ProcessControlBlock_t) * length);

    //Read priority and burst time
    for(uint32_t i = 0; i < length ; i++){
        size = read(file_descriptor, &pcb[i].remaining_burst_time, sizeof(uint32_t));
        size = read(file_descriptor, &pcb[i].priority, sizeof(uint32_t));
    }

    dyn_array_t* dynamic_array = dyn_array_import((void*)pcb, sizeof(length), sizeof(ProcessControlBlock_t), NULL);

    close(file_descriptor);
    free(pcb); 

    return dynamic_array;
}
