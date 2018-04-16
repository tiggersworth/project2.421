#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
/*
  //Need to create a function to check if it is a valid pointer
  switch (* (int *) f->esp){
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
*/
printf ("system call not available!\n");
		  thread_exit ();

}

