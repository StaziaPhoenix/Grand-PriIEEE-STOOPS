#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setAngle(double angle) {
  FILE * file;
  static double divisor = 1.8;
  file = fopen ("/dev/servoblaster","w+");
  
  double percent = angle/divisor;
  fprintf(file, "0=%f%\n", percent);
  fprintf(stdout,"0=%f%\n", percent);
  fclose (file);
}

int main () {
  int i;
  for (i = 40; i < 140; i += 5) {
    fprintf(stdout,"%d: ", i);
    setAngle(i);
    usleep(50000);
  }
  
  return 0;
}

