#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include "concurrency.h"

__attribute__((used)) unsigned char _orig_sp_hi, _orig_sp_lo;
__attribute__((used)) unsigned char _save_sp_hi, _save_sp_lo;

__attribute__((used)) void *process_malloc(unsigned int sz)
{
 if (!current_process) return (void *)malloc (sz);
 asm volatile ( "in r23,__SP_L__ \n\t"
                "sts _save_sp_lo, r23\n\t"
                "in r23,__SP_H__ \n\t"
                "sts _save_sp_hi, r23\n\t"
                "lds r23, _orig_sp_hi\n\t"
                "out __SP_H__, r23\n\t"
                "lds r23, _orig_sp_lo\n\t"
                "out __SP_L__, r23\n\t"
                "call malloc\n\t"
                "lds r23, _save_sp_hi\n\t"
                "out __SP_H__, r23\n\t"
                "lds r23, _save_sp_lo\n\t"
                "out __SP_L__, r23\n\t"
                "ret\n\t");
}

__attribute__((used)) void process_begin ()
{
  asm volatile (
		"cli \n\t"
		"in r24,__SP_L__ \n\t"
		"sts _orig_sp_lo, r24\n\t"
		"in r25,__SP_H__ \n\t"
		"sts _orig_sp_hi, r25\n\t"
		"ldi r24, 0\n\t"
		"ldi r25, 0\n\t"
		"jmp .dead_proc_entry\n\t"
		);
}

__attribute__((used)) void process_terminated ()
{
  asm volatile (
		"cli\n\t"
		"lds r25, _orig_sp_hi\n\t"
		"out __SP_H__, r25\n\t"
		"lds r24, _orig_sp_lo\n\t"
		"out __SP_L__, r24\n\t"
		"ldi r24, lo8(0)\n\t"
		"ldi r25, hi8(0)\n\t"
		"jmp .dead_proc_entry"
		);
}

void process_timer_interrupt ();

__attribute__((used)) void yield ()
{
  if (!current_process) return;
  asm volatile ("cli\n\t");
  asm volatile ("rjmp process_timer_interrupt\n\t");
}

__attribute__((used)) void process_timer_interrupt()
{
  asm volatile (
		"push r31\n\t"
		"push r30\n\t"
		"push r29\n\t"
		"push r28\n\t"
		"push r27\n\t"
		"push r26\n\t"
		"push r25\n\t"
		"push r24\n\t"
		"push r23\n\t"
		"push r22\n\t"
		"push r21\n\t"
		"push r20\n\t"
		"push r19\n\t"
		"push r18\n\t"
		"push r17\n\t"
		"push r16\n\t"
		"push r15\n\t"
		"push r14\n\t"
		"push r13\n\t"
		"push r12\n\t"
		"push r11\n\t"
		"push r10\n\t"
		"push r9\n\t"
		"push r8\n\t"
		"push r7\n\t"
		"push r6\n\t"
		"push r5\n\t"
		"push r4\n\t"
		"push r3\n\t"
		"push r2\n\t"
		"push r1\n\t"
		"push r0\n\t"
		"in r24, __SREG__\n\t"
		"push r24\n\t"
		"in r24, __SP_L__\n\t"
		"in r25, __SP_H__\n\t"
		".dead_proc_entry:\n\t"
		"rcall process_select\n\t"
		"eor r18,r18\n\t"
		"or r18,r24\n\t"
		"or r18,r25\n\t"
		"brne .label_resume\n\t"
		"lds r25, _orig_sp_hi\n\t"
		"out __SP_H__, r25\n\t"
		"lds r24, _orig_sp_lo\n\t"
		"out __SP_L__, r24\n\t"
		"ret\n\t"
		".label_resume:\n\t"
		"out __SP_L__, r24\n\t"
		"out __SP_H__, r25\n\t"
		"pop r0\n\t"
		"out  __SREG__, r0\n\t"
		"pop r0\n\t"
		"pop r1\n\t"
		"pop r2\n\t"
		"pop r3\n\t"
		"pop r4\n\t"
		"pop r5\n\t"
		"pop r6\n\t"
		"pop r7\n\t"
		"pop r8\n\t"
		"pop r9\n\t"
		"pop r10\n\t"
		"pop r11\n\t"
		"pop r12\n\t"
		"pop r13\n\t"
		"pop r14\n\t"
		"pop r15\n\t"
		"pop r16\n\t"
		"pop r17\n\t"
		"pop r18\n\t"
		"pop r19\n\t"
		"pop r20\n\t"
		"pop r21\n\t"
		"pop r22\n\t"
		"pop r23\n\t"
		"pop r24\n\t"
		"pop r25\n\t"
		"pop r26\n\t"
		"pop r27\n\t"
		"pop r28\n\t"
		"pop r29\n\t"
		"pop r30\n\t"
		"pop r31\n\t"
		"reti\n\t");
}


/*
 * Stack: save 32 regs, +2 for entry point +2 for ret address
 */
#define EXTRA_SPACE 37
#define EXTRA_PAD 4

process_t *list_head = NULL;
process_t *current_process = NULL;

unsigned int process_init (void (*f) (void), int n)
{
  unsigned long stk;
  int i;
  unsigned char *stkspace;

  /* Create a new process */
  n += EXTRA_SPACE + EXTRA_PAD;
  stkspace = (unsigned char *) process_malloc (n);

  if (stkspace == NULL) {
    /* failed! */
    return 0;
  }

  /* Create the "standard" stack, including entry point */
  for (i=0; i < n; i++) {
      stkspace[i] = 0;
  }

  n -= EXTRA_PAD;

  stkspace[n-1] = ( (unsigned int) process_terminated ) & 0xff;
  stkspace[n-2] = ( (unsigned int) process_terminated ) >> 8;
  stkspace[n-3] = ( (unsigned int) f ) & 0xff;
  stkspace[n-4] = ( (unsigned int) f ) >> 8;

  /* SREG */
  stkspace[n-EXTRA_SPACE] = SREG;

  stk = (unsigned int)stkspace + n - EXTRA_SPACE - 1;

  return stk;
}


int process_create (void (*f) (void), int n){

	unsigned int new_proc = process_init(*f, n);

	if(new_proc == 0){
		return -1;
	}
	process_t * new_node = malloc(sizeof(process_t));
	if(new_node == NULL){
		return -1;
	}

	if(list_head == NULL){ //put the first and nly item in linked list
		list_head = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
	}
	else{ //stick new node inbetween head and the one after head
		process_t * before = list_head;
		process_t * after = list_head->next;
		before->next = new_node;
		after->prev = new_node;
		new_node->next = after;
		new_node->prev = before;

	}

	new_node->sp = new_proc;
	return 0;
}


void process_start (void){
	
	// if(list_head != NULL){
		// current_process = NULL; //list_head->sp;
		process_begin();
	// }

}

void remove_current(){
	if (current_process->next == current_process){
		free(current_process);
		list_head = NULL;
    current_process = list_head;
	}
	else{
		current_process->prev->next = current_process->next;
		current_process->next->prev = current_process->prev;

		if(list_head == current_process){
			list_head = current_process->next;
		}

		unsigned int temp = current_process;
		current_process = current_process->next;
		free(temp);
	}
}

int count = 0;

unsigned int process_select (unsigned int cursp){
  // count ++;
  // if(count % 2 != 6){
  //   return list_head;
  // }

  
	if(cursp == 0){
    //return 0;
    if (current_process == NULL && list_head != NULL){
      current_process = list_head;
      return list_head->sp;
    }
		//either no running processes or current process is terminated
    else{
      remove_current(); //remove current process and update current_Process to the next item in list
      if(current_process == NULL){
        return 0;
      }
      else{
        //current process has terminated
        return current_process->sp;
      }
    }
	}
	//cursp != 0
	else{ 
    current_process = current_process->next;
	  return current_process->sp;
  }

}