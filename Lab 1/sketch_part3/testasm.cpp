#include "testasm.h"

/* the attribute "used" tells the compiler to not inline this function */
__attribute__((used))
unsigned int testasm(unsigned char a) {
  unsigned int out;

  asm volatile (R"(

   rjmp start_of_assembly

   .data
   ; any data values/static storage can go here

   .text

start_of_assembly:
   ; Your assembly language program goes here
   ;
   ; For this example, your program must not modify any registers other than 
   ; r24 and r25. In other words, save and restore all the registers that
   ; are modified by your code.

   ; Tell the compiler to move the arguments a, b into registers 
   ; r24, r25 respectively
   ;
   mov r24,%1
   ;
   ;  --- YOUR CODE GOES HERE ---
   ;       r24 = a, 
   ;

 fib:
 ; Check if n <= 1, if so jump to base-case
    ldi r25, 1
    cp r25, r24
    brge basecase
;recursive case, first call fib on n-1
  dec r24
  push r24
  call fib
;load n-2 into r24 in preparation for next call
  mov r26, r24
  pop r24
  dec r24
;before second recursive call, store result of fib(n-1) on stack in current stack frame
;stack will grow during fib(n-2) call but then will return back to its current state after fib(n-2) returns
  push r25
  push r26
;call fib on n-2
  call fib
;stack has returned to state of holding result of fib(n-1), which can be popped
;pop result of fib(n-1) from stack and add it to fib(n-2) result
  pop r26
  add r24, r26
  pop r27
  adc r25, r27
  ret
;base case, simply set r25 to 0 and return n (if n = 0 or 1)
  basecase:
  ldi r25, 0
  ret
   ;
   ;  --- YOUR CODE ENDS ---
   ;      The result must be in the register pair r25:r24
   ;      You can also rjmp to the label end_of_assembly if you need to.
   ;
end_of_assembly: 
   ; -- move r25:r24 to the 16-bit word in variable out
   movw %0,r24

)" : "=w" (out)  /* out is %0, and a 16-bit variable that is modified
		    by the assembly language */
   : "r" (a)  /* a is %1, b is %2, both are register-sized
			  variables */
   : "r27", "r26", "r25", "r24");   /* r24, r25 are modified by this assembly
			 language fragment */

  return out;
}
