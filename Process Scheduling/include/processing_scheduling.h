#ifndef PROCESS_SCHEDULING_H
#define PROCESS_SCHEDULING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dyn_array.h"

typedef struct {
    uint32_t remaining_burst_time;  // the remaining burst of the pcb
    uint32_t priority;				// The priority of the task
    bool started;                   // If it has been activated on virtual CPU
} ProcessControlBlock_t;			// you may or may not need to add more elements

typedef struct {
    float average_latency_time;     // the average waiting time in the ready queue until first schedue on the cpu
    float average_wall_clock_time;  // the average completion time of the PCBs
    unsigned long total_run_time;   // the total time to process all the PCBs in the ready queue
} ScheduleResult_t;

// Reads the PCB burst time values from the binary file into ProcessControlBlock_t remaining_burst_time field
// for N number of PCB burst time stored in the file.
// \param input_file the file containing the PCB burst times
// \return a populated dyn_array of ProcessControlBlocks if function ran successful else NULL for an error
dyn_array_t *load_process_control_blocks(const char *input_file);

// Runs the First Come First Serve Process Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for first come first serve stat tracking \ref ScheduleResult_t
// \return true if function ran successful else false for an error
bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result);

// Runs the Priority Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for shortest job first stat tracking \ref ScheduleResult_t
// \return true if function ran successful else false for an error
bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result);


// ----------------- GRADUATE STUDENTS OR UNDERGRADUATE STUDENT BONUS ----------------------

#ifdef GRAD_TESTS  // enable this in the cmake.
// Runs the Round Robin Process Scheduling algorithm over the incoming ready_queue
// \param ready queue a dyn_array of type ProcessControlBlock_t that contain be up to N elements
// \param result used for first come first serve stat tracking \ref ScheduleResult_t
// \param the quantum
// \return true if function ran successful else false for an error
bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum);
#endif

#ifdef __cplusplus
}
#endif
#endif
