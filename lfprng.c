#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

static struct proc_dir_entry *proc_entry;

int lfprng_read_proc(){
}

int lfprng_write_proc(){
}

void create_lfprng(){
}

void calc_lfprng(){
}

void seed(){
//	get thread number => check what is omp_get_thread_num and omp_get_num_threads
//	if no seed input, pick a random seed
//	set each thread a seed(seedn2 = seedn1*mult % PMOD)
//	figure out random last
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

