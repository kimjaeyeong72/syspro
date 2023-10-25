#include <stdio.h> 

int main(int argc, char* argv[])
{
   struct rec;
   FILE *fp;
   if (argc != 2) {
      fprintf(stderr, “How to use: %s FileName\n”, argv[0]);
      return 1;
   }
   fp = fopen(argv[1], "w");
   printf("%-9s %-7s %-4d %-5s %-5s %-5d\n", “ID", “bookName", “author", "year","numofborrow","borrow);
   while (scanf("%s %s %d %s %s %d", &rec.ID, rec.bookName, &rec.author, &rec.year, &rec.numofborrow,&rec.borrow)==6)
      fprintf(fp, "%s %s %d %s %s %d", &rec.ID, rec.bookName, &rec.author, &rec.year, &rec.numofborrow,&rec.borrow);
   fclose(fp);
   return 0;
}

