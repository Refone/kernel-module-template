#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/mm.h>

#include <asm/page.h>

static int __init hi(void)
{
	u64 paddr;
	u64 *vaddr;
	struct page *p = alloc_page(GFP_KERNEL | __GFP_ZERO);

    printk(KERN_INFO "module page being loaded.\n");

	if (!p) {
		printk("page alloc failed. no memory");
		return 0;
	}

	paddr = page_to_phys(p);
	vaddr = __va(paddr);

	printk("paddr[%016llx] vaddr[%016llx]\n", paddr, (u64)vaddr);

	__free_page(p);	

    return 0;
}

static void __exit bye(void)
{
    printk(KERN_INFO "module page being unloaded.\n");
}

module_init(hi);
module_exit(bye);

MODULE_LICENSE("GPL"); 
