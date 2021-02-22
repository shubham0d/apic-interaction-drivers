#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>

#define IA32_APIC_BASE		0x1B


bool local_apic_present(void)
{

    int getApicState = 0;
    int apicBit = 0;
    __asm__("mov $1, %rax");
    __asm__("cpuid");
    __asm__("mov %%edx , %0\n\t":"=r" (getApicState));
    apicBit = (getApicState >> 9) & 1;
    if (apicBit == 1){
        return true;
    }
    else {
        return false;
    }
    return false;

}

static int my_init(void)
{
	uint64_t apic_base = 0x0;
	uint8_t apic_global = 0;
	uint32_t apic_base_addr = 0;
	printk(KERN_INFO "Hello world!.\n");
	
	if (local_apic_present())
	{
		printk(KERN_INFO "Local APIC is present!.\n");
	}
	else
	{
		printk(KERN_INFO "Local APIC is not present.\n");
	}

    rdmsrl(IA32_APIC_BASE, apic_base);
    printk(KERN_INFO "APIC_BASE return %llx.\n", apic_base);
    apic_global = (apic_base >> 11) & 1;
    printk(KERN_INFO "Local global APIC flag is %x.\n", apic_global);
    apic_base_addr = (apic_base >> 12) & 0x7FFFFF;
    printk(KERN_INFO "Local APIC base is %x.\n", apic_base_addr);
    return  0;
}
   
static void my_exit(void)
{
    printk(KERN_INFO "Goodbye world.\n");

    return;
}
   
module_init(my_init);
module_exit(my_exit);



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shubham Dubey <shubham0d@protonmail.coms>");
MODULE_DESCRIPTION("Local APIC presence check");
