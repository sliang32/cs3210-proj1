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


long long getRandNumber(int pid, int tid, long long seed, struct process_id procID){
	struct list_head *temp;
	struct thread_id *traverse_thread;
	list_for_each(temp, &procID.threds){
		traverse_thread = list_entry();
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

