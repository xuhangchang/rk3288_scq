#include <dt-bindings/gpio/gpio.h>
#include <linux/module.h> 
#include <linux/kernel.h> 
#include <linux/init.h> 
#include <linux/err.h> 
#include <linux/fs.h> 
#include <linux/cdev.h> 
#include <linux/device.h> 
#include <linux/types.h>

#include <linux/gpio.h> 
#include <linux/io.h> 
#include <linux/of.h> 
#include <linux/of_gpio.h> 
#include <linux/of_platform.h> 
#include <linux/interrupt.h> 
#include <linux/platform_device.h> 
#include <linux/workqueue.h>
#include <linux/uaccess.h>

#include <linux/types.h>

#define GPIO_7_A2 226  //out_1
#define GPIO_4_D3 155  //out_2
#define GPIO_1_D3 59   //out_3
#define GPIO_3_C1 113  //out_4
#define GPIO_1_D0 56   //out_5
#define GPIO_2_A7 71   //out_6
#define GPIO_1_D1 57   //in_1
#define GPIO_2_B0 72   //in_2
#define GPIO_1_D2 58   //in_3
#define GPIO_2_B1 73   //in_4
#define GPIO_2_B2 74   //in_5



static struct class *gz_gpio_class;  
static struct device *gz_gpio_device; 

static int retval;
static dev_t gz_dev_t;
static struct cdev gz_cdev;



static int gz_gpio_open(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t gz_gpio_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	unsigned char val = 0;
	unsigned char temp_val = 0;


	temp_val = gpio_get_value(GPIO_1_D1);
	printk("read value[0] = %x\n",temp_val);
	val |= temp_val << 0;
	temp_val = gpio_get_value(GPIO_2_B0);
	printk("read value[0] = %x\n",temp_val);
	val |= temp_val << 1;
	temp_val = gpio_get_value(GPIO_1_D2);
	printk("read value[0] = %x\n",temp_val);
	val |= temp_val << 2;
	temp_val = gpio_get_value(GPIO_2_B1);
	printk("read value[0] = %x\n",temp_val);
	val |= temp_val << 3;
	temp_val = gpio_get_value(GPIO_2_B2);
	printk("read value[0] = %x\n",temp_val);
	val |= temp_val << 4;

	retval = copy_to_user(buf,&val, size); 
	if(retval)
		return -1;

	return 0;
}

static ssize_t gz_gpio_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned char val[2] = {0};
	
	printk("size %x\n",size);
	if(2 != size)
		return -1;
	retval = copy_from_user(val, buf, size); 
	printk("write value[0] = %x, value[1] = %x,\n",val[0],val[1]);
	if(retval)
		return -1;
	printk("retval = %d , write value[0] = %x, value[1] = %x,\n",retval,val[0],val[1]);
	switch(val[0])
		{
		case 0x01:
			gpio_direction_output(GPIO_7_A2, val[1]);
			break;
		case 0x02:
			gpio_direction_output(GPIO_4_D3, val[1]);
			break;
		case 0x03:
			gpio_direction_output(GPIO_1_D3, val[1]);
			break;
		case 0x04:
			gpio_direction_output(GPIO_3_C1, val[1]);
			break;
		case 0x05:
			gpio_direction_output(GPIO_1_D0, val[1]);
			break;
		case 0x06:
			gpio_direction_output(GPIO_2_A7, val[1]);
			break;

	}


	return 0;

}


static int gz_gpio_release (struct inode *inode, struct file *file)
{
	return 0;
}




struct file_operations gz_gpio_fops = {
	.owner   =  THIS_MODULE,
    .open    =  gz_gpio_open,     
	.read	 =	gz_gpio_read,
	.write	 =	gz_gpio_write,
	.release =  gz_gpio_release,
//	.fasync	 =  gz_gpio_fasync,
};


static int gz_gpio_probe(struct platform_device *pdev)
{     
	int ret = -1;
	int gpio, value;
	enum of_gpio_flags flag;
//	struct device_node *gz_gpio_node = pdev->dev.of_node;
	struct device_node *gz_gpio_node = pdev->dev.of_node;  	
	value = 0;
	printk("Firefly GPIO Test Program Probe\n");
 
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_out_1", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_out_1: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_out_1: %d\n",gpio);
  
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_out_2", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_out_2: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_out_2: %d\n",gpio);
	
  
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_out_3", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_out_3: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_out_3: %d\n",gpio);
	  
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_out_4", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_out_4: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_out_4: %d\n",gpio);
   
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_out_5", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_out_5: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_out_5: %d\n",gpio);
	
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_out_6", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_out_6: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_out_6: %d\n",gpio);
  
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_in_1", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_in_1: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_in_1: %d\n",gpio);
 
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_in_2", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_in_2: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_in_2: %d\n",gpio);
	   
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_in_3", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_in_3: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_in_3: %d\n",gpio);
	  
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_in_4", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_in_4: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_in_4: %d\n",gpio);
	  
	gpio = of_get_named_gpio_flags(gz_gpio_node, "gpio_in_5", 0, &flag);
	if (!gpio_is_valid(gpio)){
			printk("invalid gpio_in_5: %d\n",gpio);
			return -1;
	} 
	printk("valid gpio_in_5: %d\n",gpio);
			
	printk("Firefly GPIO Test Program Probe\n");
	

	
	
	if (gpio_request(GPIO_7_A2, "out_1")) {
			printk("gpio %d request failed!\n",GPIO_7_A2);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_7_A2);
	gpio_direction_output(GPIO_7_A2, value);
	
	if (gpio_request(GPIO_4_D3, "out_2")) {
			printk("gpio %d request failed!\n",GPIO_4_D3);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_4_D3);
	gpio_direction_output(GPIO_4_D3, value);
	
	if (gpio_request(GPIO_1_D3, "out_3")) {
			printk("gpio %d request failed!\n",GPIO_1_D3);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_1_D3);
	gpio_direction_output(GPIO_1_D3, value);

	if (gpio_request(GPIO_3_C1, "out_4")) {
			printk("gpio %d request failed!\n",GPIO_3_C1);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_3_C1);
	gpio_direction_output(GPIO_3_C1, value);

	if (gpio_request(GPIO_1_D0, "out_5")) {
			printk("gpio %d request failed!\n",GPIO_1_D0);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_1_D0);
	gpio_direction_output(GPIO_1_D0, value);

	if (gpio_request(GPIO_2_A7, "out_6")) {
			printk("gpio %d request failed!\n",GPIO_2_A7);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_2_A7);
	gpio_direction_output(GPIO_2_A7, value);

	if (gpio_request(GPIO_1_D1, "in_1")) {
			printk("gpio %d request failed!\n",GPIO_1_D1);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_1_D1);
	gpio_direction_input(GPIO_1_D1);

	if (gpio_request(GPIO_2_B0, "in_2")) {
			printk("gpio %d request failed!\n",GPIO_2_B0);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_2_B0);
	gpio_direction_input(GPIO_2_B0);
	
	if (gpio_request(GPIO_1_D2, "in_3")) {
			printk("gpio %d request failed!\n",GPIO_1_D2);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_1_D2);
	gpio_direction_input(GPIO_1_D2);
	
	if (gpio_request(GPIO_2_B1, "in_4")) {
			printk("gpio %d request failed!\n",GPIO_2_B1);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_2_B1);
	gpio_direction_input(GPIO_2_B1);
	
	if (gpio_request(GPIO_2_B2, "in_5")) {
			printk("gpio %d request failed!\n",GPIO_2_B2);
			return ret;
	}
	printk("gpio %d request success!\n",GPIO_2_B2);
	gpio_direction_input(GPIO_2_B2);


	
	retval = alloc_chrdev_region(&gz_dev_t,0,1, "gz_gpio_dev");
	if (retval) {
	   printk(KERN_ERR "Unable to register minors\n");
	   return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev_region success\n");
		
	cdev_init(&gz_cdev, &gz_gpio_fops);
	retval = cdev_add(&gz_cdev, gz_dev_t, 1);
	if (retval) {
	   printk(KERN_ERR "Unable to cdev_add\n");
	   return -EINVAL;
	}
	printk(KERN_INFO "cdev_add success\n");



	gz_gpio_class = class_create(THIS_MODULE, "gz_gpio_c");  
  
    gz_gpio_device = device_create(gz_gpio_class, NULL, gz_dev_t, NULL, "gz_gpio");

    return 0; 
} 

static int gz_gpio_remove(struct platform_device *pdev)
{

    device_unregister(gz_gpio_device);  //卸载类下的设备  
	class_destroy(gz_gpio_class);


	cdev_del(&gz_cdev);
	unregister_chrdev_region(gz_dev_t, 1);

    return 0;
}





static struct of_device_id gz_match_table[] = 
{         
    {.compatible = "rk-gz-gpio"},  
	{}
}; 

static struct platform_driver gz_gpio_driver = 
{         
	.driver = {                 
		.name = "gz-gpio",                 
		.owner = THIS_MODULE,                 
		.of_match_table = of_match_ptr(gz_match_table),         
    },         
    .probe = gz_gpio_probe, 
    .remove = gz_gpio_remove,
};
 
static int gz_gpio_init(void) 
{         
	printk(KERN_ALERT "gz_gpio_init\n");
    return platform_driver_register(&gz_gpio_driver); 
} 



static void gz_gpio_exit(void) 
{         
	printk("gz_gpio_exit\n");
    platform_driver_unregister(&gz_gpio_driver); 
}
 
module_init(gz_gpio_init); 
module_exit(gz_gpio_exit); 

MODULE_AUTHOR("xuhc <xuhangchang@gzrobot.com>"); 
MODULE_DESCRIPTION("gz GPIO driver"); 
MODULE_LICENSE("GPL");
