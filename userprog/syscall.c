#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "devices/input.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "userprog/pagedir.h"



static void syscall_handler (struct intr_frame *);

struct file_process
{
	int fd;
	struct file* file;
	struct list_elem file_elem;
};

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf ("system call!\n");
  
  if(!(is_user_vaddr((const void*) f->esp)))
  {
	thread_exit(-1);
  }

  switch( *(int *) f->esp)
  {
	case SYS_HALT:
	{
		shutdown_power_off();
		break;
	}
	case SYS_EXIT:
	{
		if(!(is_user_vaddr((const void*) (f->esp+4))))
  		{
			thread_exit(-1);
  		}
		int status;
		status = *((int *) f->esp+1);
		thread_exit(status);
		break;
	}
	case SYS_EXEC:
	{
		if(!(is_user_vaddr((const void*) (f->esp+4))))
  		{
			thread_exit(-1);
  		}
		
		struct thread *cur = thread_current();
		void* filename = *(char **)(f->esp+4);
		filename = pagedir_get_page(cur->pagedir, (const void *) filename);
		
		if(!filename)
		{
			thread_exit(-1);
		}
		char *command = *(char **)(f->esp+4);
		f->eax = process_execute((const char*) command);	
			
			
		
		break;
	}
	case SYS_WAIT:
	{
		while(1);
		break;
	}	
	case SYS_CREATE:
	{
		break;
	}
	case SYS_REMOVE:
	{
		break;
	}
	case SYS_OPEN:
	{
		break;
	}
	case SYS_FILESIZE:
	{
		break;
	}
	case SYS_READ:
	{
		// int read (int fd, void *buffer, unsigned size)
		int fd = *(int *)(f->esp + 4);
		printf("fd : ");
		printf(fd);
		void *buffer = *(char **)(f->esp + 8);
		printf("buffer: ");
		printf(buffer);
		unsigned size = *(unsigned *)(f->esp + 12);
		printf("size: ");
		printf(size);
		// Read size bytes from the file open as fd into buffer
		// f->eax = number of bytes actually read (0 at end of file)
		// ERROR: f->eax = -1 if file could not be read (due to a 
		// 		   condition other than end of file).
		// Fd 0 reads from the keyboard using input_getc()
		if(fd == 0){
			int i;
			for(i=0; i < size; i++){
				buffer[i] = input_getc();
			}
			f->eax = size;
		}
		else{
			f->eax = -1;
		}
		break;
	}
	case SYS_WRITE:
	{
		break;
	}
	case SYS_SEEK:
	{
		break;
	}
	case SYS_TELL:
	{
		break;
	}
	case SYS_CLOSE:
	{
		break;
	}

  }

void exit (int status)
{
  thread_exit(status);
}
