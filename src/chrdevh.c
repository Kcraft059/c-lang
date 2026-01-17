#include <asm/io.h>
#include <asm/page.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <rpireg.h>

int chrdev_init(struct file_operations* fops) {
  // Inits a char device and stores major
  majorDev = register_chrdev(0, MOD_NAME, fops);
  int err = majorDev;

  if (err < 0)
    pr_err(MOD_NAME ": Err registering chrdev: %d\n", err);

  return err;
}

void chrdev_release(void) {
  unregister_chrdev(majorDev, MOD_NAME);
}

int fops_mmap(struct file* filp, struct vm_area_struct* vma) {
  // Print info
  pr_info(MOD_NAME ": VMA\nvm_start:\t%08x\nvm_end:\t\t%08x\nvm_pgoff:\t%08x\n",
          vma->vm_start, vma->vm_end, vma->vm_pgoff << PAGE_SHIFT);

  if (vma->vm_end - vma->vm_start > PAGE_SIZE) {
    pr_err(MOD_NAME ": incorrect len. %ld,%lu", vma->vm_end - vma->vm_start, PAGE_SIZE);
    return -1;
  }

  vma->vm_pgoff = virt_to_phys(testmembuffer) >> PAGE_SHIFT; // Bc phys addres is fffffxxx, as fffff page number and xxx, page offset, we onyl want page number

  int status = remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
                               vma->vm_end - vma->vm_start, vma->vm_page_prot);

  if (status) {
    pr_err(MOD_NAME ": Error remaping page frame number.\n");
    return -1;
  }

  return 0;
}

int fops_release(struct inode*, struct file*) {
  return 0;
}