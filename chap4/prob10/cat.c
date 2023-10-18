#include <stdio.h>
int main(int argc, char *argv[])
{
   FILE *fp;
   int c;
   int i;
for (i =1; i <argc; i++) {
   if (argc < 2)
      fp = stdin;
   else  fp = fopen(argv[1],"r");

   c = getc(fp);
   while (c!=EOF) {
	   putc(c,stdout);
	   c = getc(fp);
   }
   fclose(fp);
}
   return 0;
}
