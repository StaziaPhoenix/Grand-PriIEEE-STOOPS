#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ImageAnalyze.hpp"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define ADDRESS 0x04 // need to dynamically discover real each boot

static const char *devName = "/dev/i2c-1";

//char killFlag[1] = 0;
unsigned char values[2];

int main() {

    printf("I2C: Connecting\n");
    int file;
 
    if ((file = open(devName, O_RDWR)) < 0) {
        cerr << "I2C: Failed to access " << devName << endl;
        exit(1);
    }

    cerr << "I2C: acquiring bus to " << ADDRESS << endl;
 
    if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
        cerr << "I2C: Failed to acquire bus access/talk to slave " <<
                            ADDRESS << endl;
        exit(1);
    }

    ImageAnalyze imganlz;

    while(1){
        values[0] = imganlz.errorDetect(); // must encode
//        cout << "error " << (int)values[0] << endl;
        
        values[1] = 191;	// will be called once we vary speed, for now constant ~75%
        					// must encode

        cout << "Sending " << (int)values[0] << endl;
        write(file, values, 1);
 //       usleep(1000);

        /* Kill switch stuff. Not applicable yet
         * if (read(file, killFlag, 1) != 1) {
            fprintf(stderr, "I2C: Failed to read interrupt from slave 0x%x\n");
        }

        if ( (int) killFlag[0] == 1 ) {
            close(file);
            return 0;
        }*/ 
    }
}
