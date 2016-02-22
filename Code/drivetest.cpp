#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ImageAnalyze.hpp"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define ADDRESS 0x04 // need to dynamically discover real each boot

static const char *device = "/dev/i2c-1";

int file;
char killFlag[1] = 0;
unsigned char values[2];

int main() {

    printf("I2C: Connecting\n");
 
    if ((file = open(device, O_RDWR)) < 0) {
        fprintf(stderr, "I2C: Failed to access %d\n", device);
        exit(1);
    }

    printf("I2C: acquiring bus to 0x%x\n", ARDU_ADDRESS);
 
    if (ioctl(file, I2C_SLAVE, ARDU_ADDRESS) < 0) {
        fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n",
                            ARDU_ADDRESS);
        exit(1);
    }

    ImageAnalyze imganlz;

    while(1){
        values[0] = imganlz.errorDetect(); // must encode
        cout << "error " << values[0] << endl;
        
        values[1] = 191;	// will be called once we vary speed, for now constant ~75%
        					// must encode

        if (write(file, values, 1) != 1) {
            fprintf(stderr, "I2C: Failed to write to slave 0x%x\n");
        }
        usleep(10000;)

        if (read(file, killFlag, 1) != 1) {
            fprintf(stderr, "I2C: Failed to read interrupt from slave 0x%x\n");
        }

        if ( (int) killFlag[0] == 1 ) {
            close(file);
            return 0;
        } 
    }
}
