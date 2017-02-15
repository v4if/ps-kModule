#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched.h> /* init_task */

MODULE_LICENSE("Dual BSD/GPL");

static void pad_blank(int depth) {
    while(depth--) {
        printk("\t|");
    }
}

static int walk(struct task_struct *parent, int depth) {
    int ret = 0;

    struct list_head *pos = NULL;
    struct task_struct *p = NULL;

    /** 
     * #define list_for_each(pos, head) \
     * for (pos = (head)->next; pos != (head); pos = pos->next)
     **/
    list_for_each(pos, &parent->children) {
        // 从一个结构的成员地址找到其容器的指针
        p = list_entry(pos, struct task_struct, sibling);

        pad_blank(depth);
        printk("——%s[#%d]\n", p->comm, p->pid);

        ret += walk(p, depth + 1) + 1;
    }

    return ret;
}

static int _ps_list_init(void) {
    int count = walk(&init_task, 0);
    printk(KERN_EMERG "the number of process is %d\n", count);
    return 0;
}

static void list_process_exit(void)
{
    printk(KERN_EMERG "%s(),line %d\n", __FUNCTION__, __LINE__);
}

module_init(_ps_list_init);
module_exit(list_process_exit);
