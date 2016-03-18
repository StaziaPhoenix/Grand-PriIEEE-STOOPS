#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
 
// The PiWeather board i2c address
#define ADDRESS 0x04

int file;
unsigned char values[2] = {0,1};
 
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";
 
int main(int argc, char** argv) {
 
  printf("I2C: Connecting\n");

 
  if ((file = open(devName, O_RDWR)) < 0) {
    fprintf(stderr, "I2C: Failed to access %d\n", devName);
    return 1;
  }
 
  printf("I2C: acquiring buss to 0x%x\n", ADDRESS);
 
  if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
    fprintf(stderr, 
	"I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
    exit(1);
  }
 
  int i;
  for (i = 0; i < 180; i = i+10) {
    values[0] = i;

    printf("Sending %d\n", values[0]);
    write(file, values, 1);
    usleep(150000);
  }
 
    values[0] = 90;
    printf("Sending %d\n", values[0]);
    write(file, values, 1);

  // Now wait else you could crash the arduino by sending requests too fast
  usleep(10000);
 
  close(file);
  return 0;
}
