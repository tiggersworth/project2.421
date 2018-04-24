#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
//static void valid_pointer_check(int UNSURE);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  int * usr_ptr = f->esp;
  //valid_pointer_check(usr_ptr);
  //Need to create a function to check if it is a valid pointer
  //(* (int *) f->esp)  ----> * usr_ptr
  switch (* usr_ptr){
	  case SYS_HALT:
		  {
			  shutdown_power_off();
			  break;
		  }
	  case SYS_EXIT:
		  {
			  //What sys_exit will do
			  break;
		  }
          case SYS_EXEC:
		  {
			  //What sys_exec will do
			  break;
		  }
	  case SYS_WAIT:
		  {
			  //What sys_wait will do
			  break;
		  }
          case SYS_CREATE:
		  {
			  //What sys_create will do
			  break;
		   }
          case SYS_REMOVE:
		  {
			  //What sys_remove will do
			  break;
			   }
          case SYS_OPEN:
		  {
			  //What sys_open will do
			  break;
			   }
          case SYS_FILESIZE:
		  {
			  //What sys_filesize will do
			  break;
			   }
          case SYS_READ:
		  {
			  //What sys_read will do
			  break;
			   }
          case SYS_WRITE:
		  {
			  //What sys_write will do
			  break;
			   }
          case SYS_SEEK:
		  {
			  //What sys_seek will do
			  break;
			   }
          case SYS_TELL:
		  {
			  //What sys_tell will do
			  break;
		   }
          case SYS_CLOSE:
		  {
			  //What sys_close will do
			  break;
		  }
          default:
		  {
		  printf ("system call not available!\n");
		  thread_exit ();
		  }
}
/*
printf ("system call not available!\n");
		  thread_exit ();
*/

}

/* Need a function that checks the validity of user pointer */
/*
static void valid_pointer_check(int* usr_ptr){
	switch(UNSURE){
		case (&usr_ptr == NULL):	
			{
			//Kill Process and Free Its Resources
			kill_process();
			}
		case (usr_ptr >= PHYS_BASE):	
			{
			//Kill Process and Free Its Resources
			kill_process();
			}
		case (//Mapped to an unmapped memory location):
			{
			//Kill Process and Free Its Resources
			kill_process();
			}
		default:
			{
			//Do Nothing
			}
	}
}
*/

/* Prof. Kosar: "Process is a single thread. So, you can use thread_exit() to kill the process." */
static void kill_process(){
	thread_exit();
}





