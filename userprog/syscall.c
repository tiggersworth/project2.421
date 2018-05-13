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
#include "userprog/process.h"


static void syscall_handler (struct intr_frame *);

struct file_process
{
	int fd;
	struct file* file_name;
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
  //printf ("system call!\n");
  
  if(!(is_user_vaddr((const void*) f->esp)))
  {
	thread_exit(-1);
  }

  switch( *(int *) f->esp)
  {
	case SYS_HALT:
	{
		//printf("sys_halt \n");
		halt();
		break;
	}
	case SYS_EXIT:
	{
		//printf("sys_exit \n");
		/*if(!(is_user_vaddr((const void*) (f->esp+4))))
  		{
			thread_exit(-1);
  		}*/
		check_ptr((const void*) (f->esp+4));
		int status;
		status = *((int *) f->esp+1);
		exit(status);
		break;
	}
	case SYS_EXEC:
	{
		//printf("sys_exec \n");
		/*if(!(is_user_vaddr((const void*) (f->esp+4))))
  		{
			thread_exit(-1);
  		}*/
		check_ptr((const void*) (f->esp+4));
					
			
		
		break;
	}
	case SYS_WAIT:
	{
		//printf("sys_wait \n");
	
		break;
	}	
	case SYS_CREATE:
	{
		//printf("sys_create \n");
		break;
	}
	case SYS_REMOVE:
	{
		//printf("sys_remove \n");
		break;
	}
	case SYS_OPEN:
	{
		//printf("sys_open \n");
		check_ptr((const void*) (f->esp+4));
		struct thread *cur = thread_current();

		void* filename = *(char **)(f->esp+4);
		filename = pagedir_get_page(cur->pagedir, (const void *) filename);

		if(filename == NULL)
		{
			thread_exit(-1);
		}
		else
		{
			f->eax = open((const char*)(filename));
		
		}
		break;
	}
	case SYS_FILESIZE:
	{
		//printf("sys_filesize \n");
		break;
	}
	case SYS_READ:
	{
		//printf("sys_read \n");
		break;
	}
	case SYS_WRITE:
	{
		//printf("sys_write \n");
		
		check_ptr((const void*) (f->esp+4));
		check_ptr((const void*) (f->esp+8));
		check_ptr((const void*) (f->esp+12));
		
		int file_des = *(int *)(f->esp+4);
		
		if(file_des == 0)
		{thread_exit(-1);}

		void *buf = *(char **) (f->esp+8);
		unsigned length = *(unsigned *)(f->esp+12);

		struct thread *cur = thread_current();
		buf = pagedir_get_page(cur -> pagedir, (const void*) buf); 	
		
		if(!buf){thread_exit(-1);}

		f->eax = write(file_des, buf, length);		
		break;
	}
	case SYS_SEEK:
	{
		//printf("sys_seek \n");
		break;
	}
	case SYS_TELL:
	{
		//printf("sys_tell \n");
		break;
	}
	case SYS_CLOSE:
	{
		//printf("sys_close \n");
		break;
	}

  }
}

void halt (void)
{
  shutdown_power_off();
}

void exit (int status)
{
  //printf("exiting program");
  thread_exit(status);
}

int write(int fd, const void* buffer, unsigned size)
{
	int bytes;
	
	if(fd==1)
	{
		putbuf(buffer, size);
		bytes = size;	
	}

	return bytes;
}

tid_t exec(const char *cmd_line)
{
	int tid;
	tid = process_execute(cmd_line);

	return tid;
}

int open(const char *file)
{
	struct file *open_file = filesys_open(file);
	
	struct thread *cur = thread_current();

	if(open_file)
	{
		if(cur-> file_descriptor < 2)
		{
			cur-> file_descriptor = 2;
		}	
		
		struct file_process *fp = malloc(sizeof(struct file_process));
		fp -> fd = thread_current() -> file_descriptor;
		thread_current() -> file_descriptor = thread_current() -> file_descriptor+1;
		fp -> file_name = open_file;
		

		list_push_front(&cur->file_list, &fp-> file_elem);
	}	
	else if (open_file == NULL){return -1;}


	return thread_current() -> file_descriptor;
	


}

void check_ptr(const void* vaddr)
{
	if(!(is_user_vaddr((const void *) (vaddr) )))
  		{
			thread_exit(-1);
  		}
}

