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

/*struct file_process
{
	int fd;
	struct file* file;
	struct list_elem file_elem;
};*/

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}


static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //printf ("system call!\n");

	//printf("%d\n",f->esp);

  
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
		if(!(is_user_vaddr((const void*) (f->esp+4))))
  		{
			thread_exit(-1);
  		}
		int status;
		status = *((int *) f->esp+1);
		exit(status);
		break;
	}
	case SYS_EXEC:
	{
		//printf("sys_exec \n");
		if(!(is_user_vaddr((const void*) (f->esp+4))))
  		{
			thread_exit(-1);
  		}
		
		struct thread *cur = thread_current();
		void* filename = *(char **)(f->esp+4);
		filename = pagedir_get_page(cur->pagedir, (const void *) filename);
		
		if(filename == NULL)
		{
			thread_exit(-1);
		}
		char *command = *(char **)(f->esp+4);
		
		f->eax = exec((const char*) command);	
			
			
		
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
	check_ptr((const void*) (f->esp+4));
		  
  	char *s = *(char **)(f->esp + 4);
  	f->eax = open(s);

		

		
		break;
	}
	case SYS_FILESIZE:
	{
		//printf("sys_filesize \n");
		break;
	}
	case SYS_READ:
	{
		
		
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


struct file_process
{
	int fd;
	struct file* file;
	struct list_elem file_elem;
};



  static struct file_process* get_file_process(int fd)
{

  struct list_elem *e;
  struct file_process *file_entry = NULL;
  struct list *fd_table = &thread_current()->file_list;
  

  while(e != list_end(fd_table)){
      e= list_next(e);
      if((list_entry (e, struct file_process,file_elem))->fd != fd){
	continue;
      }else{
	file_entry = list_entry (e, struct file_process,file_elem);
        break;
       }
   }

   return file_entry;
  
	
      
  }


static int put (void)
{
  return thread_current()->file_descriptor++;
}

int open(const char *fname){
struct file_process *file_process = malloc (sizeof(struct file_process));
struct file * f = filesys_open (fname);
  if (f == NULL || file_process == NULL){
    return -1;
}

  file_process->fd = put();
  file_process->file = f;
  list_push_back(&thread_current()->file_list, &file_process
   ->file_elem);

  return file_process->fd;
	

}





tid_t exec(const char *cmd_line)
{
	tid_t tid;
	tid = process_execute(cmd_line);

	return tid;
}



void check_ptr(const void* vaddr)
{
	if(!(is_user_vaddr(vaddr)))
  		{
			thread_exit(-1);
  		}
}
