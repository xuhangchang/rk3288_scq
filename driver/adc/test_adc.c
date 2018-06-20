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
	fd = open("/dev/gz_adc", O_RDWR);
	if (fd < 0)
	{
		printf("can't open!\n");
	}

	
	int val_r;
	while(1)
	{
			read(fd, &val_r, 4);
			printf("%d\n",val_r);
			usleep(50000);
	}
	

	return 0;
}
