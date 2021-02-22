#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <sound/initval.h>
#include <asm/io.h>



static int my_init(void)
{

	printk(KERN_INFO "Hello world!.\n");
    phys_addr_t apic_base_phys = 0xfee00000; // fee00000
	void __iomem *mapped = ioremap(apic_base_phys + 0x30, 0x4);

	if(mapped == NULL){
		printk(KERN_INFO "nullpointer\n");
	} else {
		uint32_t value = ioread32(mapped);
		printk(KERN_INFO "Value: %x\n", value); // 0xffffffff
	}

	iounmap(mapped);
    
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
MODULE_DESCRIPTION("Local APIC register interaction");
