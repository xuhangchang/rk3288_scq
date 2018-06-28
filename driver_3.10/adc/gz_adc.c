#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <asm/irq.h>
#include <linux/iio/consumer.h>

#ifdef CONFIG_OF
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#endif

static struct class *gz_adc_class;
static struct device *gz_adc_device;
static struct device *gz_adc_dev = NULL;

static dev_t gz_dev_t;
static int retval;
static struct cdev gz_cdev;

static int gz_adc_probe(struct platform_device *pdev)
{
	    printk("%s probe \n", __FUNCTION__);
        /*Get io channel*/
        gz_adc_dev = &pdev->dev;     
        return 0;
        
}

static int gz_adc_remove(struct platform_device *pdev)
{
        return 0;
}

static const struct of_device_id of_gz_adc_match[] = {
		{ .compatible = "gz-adc0" },	
//		{ .compatible = "rockchip,saradc" },
        { /* Sentinel */ }
};

static struct platform_driver gz_adc_driver = {
        .probe = gz_adc_probe,
        .remove = gz_adc_remove,
        .driver = {
                .owner = THIS_MODULE,
                .name  = "gz-adc2",
#ifdef CONFIG_OF
                .of_match_table  = of_gz_adc_match,
#endif
        },
};

static ssize_t gz_adc_read(struct file *filep, char __user *usrbuf, size_t size, loff_t *offset)
{
        
        int val,ret;
        struct iio_channel *chan; //定义 IIO 通道结构体

        printk("%s \n", __FUNCTION__);
        chan = iio_channel_get(gz_adc_dev, NULL); //获取 IIO 通道结构体
        ret = iio_read_channel_raw(chan, &val);

		
		val = (1800 * val) / 1023;
//       printk("gz_adc value = %u \n", val);
        if (ret < 0)
        {
                printk("Read channel failed. \n");
                return EIO;
        }
        ret = copy_to_user(usrbuf, (void *)&val, size);
		if(ret)
			return -1;

         return 0;
}
static ssize_t gz_adc_write(struct file *filep, const char __user *usrbuf, size_t size, loff_t *offset)
{
        return 0;
}

static int gz_adc_open(struct inode *inode, struct file *filep)
{
        return 0;
}
static int gz_adc_release(struct inode *inode, struct file *filep)
{

        return 0;
}


static struct file_operations gz_adc_fops = {
        .owner =   THIS_MODULE,
        .read  =   gz_adc_read,
        .write =   gz_adc_write,
        .open  =   gz_adc_open,
        .release = gz_adc_release,
};

static int __init gz_adc_init(void)
{	
	retval = alloc_chrdev_region(&gz_dev_t,0,1, "gz_adc_dev");
	if (retval) {
	   printk(KERN_ERR "Unable to register minors\n");
	   return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev_region success\n");
		
	cdev_init(&gz_cdev, &gz_adc_fops);
	retval = cdev_add(&gz_cdev, gz_dev_t, 1);
	if (retval) {
	   printk(KERN_ERR "Unable to cdev_add\n");
	   return -EINVAL;
	}
	printk(KERN_INFO "cdev_add success\n");



	gz_adc_class = class_create(THIS_MODULE, "gz_adc_c");  
  
    gz_adc_device = device_create(gz_adc_class, NULL, gz_dev_t, NULL, "gz_adc");
		
		
	platform_driver_register(&gz_adc_driver);
	
	
	return 0;
}

static void __exit gz_adc_exit(void)
{
	platform_driver_unregister(&gz_adc_driver);
	device_unregister(gz_adc_device);  //卸载类下的设备  
	class_destroy(gz_adc_class);


	cdev_del(&gz_cdev);
	unregister_chrdev_region(gz_dev_t, 1);
}

module_init(gz_adc_init);
module_exit(gz_adc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuhc <xuhangchang@gzrobot.com>"); 