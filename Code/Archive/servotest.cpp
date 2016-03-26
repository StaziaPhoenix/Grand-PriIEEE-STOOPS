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
 
  cout << "I2C: Connecting\n" << endl;
  
  int file;
  if ((file = open(devName, O_RDWR)) < 0) {
    cerr << "I2C: Failed to access \n" << devName << endl;
    exit(1);
  }
 
  cerr << "I2C: acquiring bus to \n" << ADDRESS << endl;
 
  if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
    cerr << "I2C: Failed to acquire bus access/talk to slave 0x\n" <<
           ADDRESS << endl;
    exit(1);
  }
 
  if ((file = open(devName, O_RDWR)) < 0) {
    cerr << "I2C: Failed to access \n" << devName << endl;
    return 1;
  }
 
  cerr << "I2C: acquiring buss to 0x\n" << ADDRESS << endl;
 
  if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
    cerr <<
	"I2C: Failed to acquire bus access/talk to slave \n" << ADDRESS << endl;
    exit(1);
  }
 
  int i;
  for (i = 0; i < 180; i = i+10) {
    values[0] = i;

    /*if (i % 20 == 0) {
      values[1] = 64;
    } else {
      values[1] = 255;
    }*/

    printf("Sending %d, %d\n", values[0], values[1]);
    write(file, values, 1);
    usleep(1000000);
  }
 

  // Now wait else you could crash the arduino by sending requests too fast
  usleep(10000);
 
  close(file);
  return 0;
}
