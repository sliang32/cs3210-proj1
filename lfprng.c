#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/current.h>
#include <linux/cdev.h>

static struct proc_dir_entry *proc_entry;
struct process_id* procID;

static const long long MULTIPLIER = 764261123;
static const long long PMOD = 2147483647;
static const long long ADDER = 0;

struct process_id{
	int pid;
	int current_thread;
	struct list_head threads;
	long long seed;
	boolean updated;
}

struct thread_id{
	int tid;
	long long seed;
	struct list_head thread_list;
}

static int lfprng_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{  
	long long val = getRandNumber(current->tgid, current->pid, procID.seed);

	int length = sprintf(page, "%lld", val);

  	return length;
}//end lfprng_read_proc function

static int lfprng_write_proc(struct file *file, const char *buf, usingned long count, void *data)
{
    	static const int SEED_SIZE = sizeof(long long);
	long long seed;

	if(count> SEED_SIZE)
	{
		count = SEED_SIZE;
	}//end if statement
        if(copy_from_user(&seed, buf, count))
    	{
    		return -EFAULT;
    	}
	setSeed(seed, current->tgid);
	
	return count;
}//end lfprng_write_proc function

long long getRandNumber(int tid, struct process_id *procID){
	struct list_head *temp1;
	struct list_head *temp2;

	struct thread_id *traverse_thread;
	struct thread_id *head;

	long long seed, nextSeed;
	list_for_each(temp1, &procID->threads){
		head = list_entry(temp1, struct thread_id, list);
	}
	list_for_each(temp2, &head->list){
		traverse_thread = list_entry(temp2, struct thread_id, list);
		if(traverse_thread->tid == head->current_thread){
			seed = traverse_thread->seed;
			next_seed = (seed * MULTIPLIER + ADDER) % PMOD;
		}else if(traverse_thread->tid > head->current_thread){
			seed = next_seed;
			traverse_thread->seed = next_seed;
			if(traverse_thread->tid == tid){
				head->current_thread = tid;
				return next_seed;
			}
			next_seed = (seed * MULTIPLIER + ADDER) % PMOD;		
		}
	}
	list_for_each(temp2, &head->list){
		traverse_thread = list_entry(temp2, struct thread_id, list);
		if(traverse_thread->tid <= tid){
			seed = next_seed;
			traverse_thread->seed = next_seed;
			if(traverse_thread->tid == tid){
				head->current_thread = tid;
				return next_seed;
			}
			next_seed = (seed * MULTIPLIER + ADDER) % PMOD;		
		}
	}
	return 0;
}

void setSeed(long long seed, struct process_id *procID){
	struct list_head *temp1;
	struct list_head *temp2;
	struct thread_id *traverse_thread;
	struct thread_id *head;

	long long nextSeed = seed;
	
	head = procID->threads;
	list_for_each(temp2, &head->list){
		traverse_thread = list_entry(temp2, struct thread_id, list);
		seed = next_seed;
		traverse_thread->seed = next_seed;
		next_seed = (seed * MULTIPLIER + ADDER) % PMOD;
	}
}

static int __init lfprng_module_init(void){
	int rv = 0;
	proc_entry = create_proc_entry("lfprng", 0666, NULL);
	if(proc_entry == NULL){
		rv = -ENOMEN
		printk(KERN_INFO "lfprng: Couldn't create proc entry\n");
	}else{
		proc_entry->owner = THIS_MODULE;
		proc_entry->read_proc = lfprng_read_proc;
		proc_entry->write_proc = lfprng_write_proc;
		printk(KERN_INFO "lfprng_module_init called. Module now loaded.\n");
	}
	return rv;
}

static void __exit lfprng_module_cleanup(void){
	remove_proc_entry(lfprng, proc_entry);
	printK(KERN_INFO "lfprng_module_cleanup called. Module unloaded");
}

module_init(lfprng_module_init);
module_exit(lfprng_module_exit);

