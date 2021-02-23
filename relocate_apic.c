#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>

#define IA32_APIC_BASE		0x1B


static int my_init(void)
{
	uint64_t apic_base = 0x0;
	uint8_t apic_global = 0;
	uint32_t apic_base_addr = 0;
	uint64_t new_apic_base = 0;
	printk(KERN_INFO "Hello world!.\n");
	

    rdmsrl(IA32_APIC_BASE, apic_base);
    printk(KERN_INFO "APIC_BASE return %llx.\n", apic_base);
    apic_global = (apic_base >> 11) & 1;
    // change the constant value
    new_apic_base = 0xfae00000 | (apic_global << 11);
    wrmsrl(IA32_APIC_BASE, new_apic_base);
    apic_base = 0;
    
    rdmsrl(IA32_APIC_BASE, apic_base);
    printk(KERN_INFO "APIC_BASE updated is %llx.\n", apic_base);
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
MODULE_DESCRIPTION("Code to relocate Local APIC base");
