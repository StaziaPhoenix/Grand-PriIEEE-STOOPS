/* fopen example */
#include <stdio.h>
int main ()
{
  FILE * pFile;
  pFile = fopen ("/dev/servoblaster","w");
  fprintf(pFile, "0=50%");
  fclose (pFile);

  return 0;
}
