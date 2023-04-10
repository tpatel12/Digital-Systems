/*************************************************************************
 *
 *  Copyright (c) 2013--2018 Rajit Manohar
 *  All Rights Reserved
 *
 **************************************************************************
 */
#ifndef __CONCURRENCY_H__
#define __CONCURRENCY_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct process_state process_t;
   /* opaque definition of process type; you must provide this
      implementation.
   */


/*------------------------------------------------------------------------

   THE FOLLOWING FUNCTIONS MUST BE PROVIDED.

------------------------------------------------------------------------*/

/* ====== Part 1 ====== */

extern process_t *current_process; 
/* the currently running process */

__attribute__((used)) unsigned int process_select (unsigned int cursp);
/* Called by the runtime system to select another process.
   "cursp" = the stack pointer for the currently running process
*/

void process_start (void);
/* Starts up the concurrent execution */

int process_create (void (*f)(void), int n);
/* Create a new process */

/* ===== Part 2 ====== */

typedef struct lock_state lock_t;
  /* you have to define the lock_state structure */

void lock_init (lock_t *l);
void lock_acquire (lock_t *l);
void lock_release (lock_t *l);


/*-- functions provided in the .c file --*/

unsigned int process_init (void (*f) (void), int n);
void process_begin ();
void yield ();

__attribute__((used)) void *process_malloc (unsigned int sz);
/* Use this to allocate memory instead of the standard malloc() routine.
   It has the same behavior as malloc: it returns a pointer to a newly
   allocated chunk of sz bytes of memory on success.  If memory allocation 
   fails, this returns NULL. To free the allocated space, use the standard
   free() function.

   NOTE: this must be called with interrupts disabled. Also, if you use
   free(), make sure that is also called with interrupts disabled.
*/

#ifdef __cplusplus
}
#endif

#endif /* __CONCURRENCY_H__ */



