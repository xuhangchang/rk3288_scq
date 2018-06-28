#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* led_test on
 * led_test off
 */
int main(int argc, char **argv)
{
	int fd;
	int val = 1;
	fd = open("/dev/gz_gpio", O_RDWR);
	if (fd < 0)
	{
		printf("can't open!\n");
	}

	
	unsigned char val_r;
	unsigned char val_w_0[2] = {0x04,0x00};
	unsigned char val_w_1[2] = {0x04,0x01};
	write(fd,val_w_0,2);
	while(1)
	{
//			write(fd,val_w_0,2);
			read(fd, &val_r, 1);
			printf("%x\n",val_r);
			usleep(500000);
			
//			write(fd,val_w_1,2);
			read(fd, &val_r, 1);
			printf("%x\n",val_r);
			usleep(500000);
	}
	

	return 0;
}
