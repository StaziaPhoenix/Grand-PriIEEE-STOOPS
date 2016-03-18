/* fopen example */
#include <stdio.h>
int main () {
  FILE * file;
  file = fopen ("/dev/servoblaster","w+");
  fprintf(file, "0=70%\n");
  fprintf(stdout,"0=70%\n");
  fclose (file);

  return 0;
}
