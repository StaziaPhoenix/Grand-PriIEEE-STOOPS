/* fopen example */
#include <stdio.h>
int main () {
  FILE * file;
  file = fopen ("/dev/servoblaster","w+");
  fprintf(file, "0=50%%");
  fprintf(stdout,"0=50%%");
  fclose (file);

  return 0;
}
