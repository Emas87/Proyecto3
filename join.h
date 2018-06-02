#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void join(){

   FILE *fp_begin = fopen("begin.txt", "r");
   FILE *fp_edit_RM = fopen("edit_RM.txt", "r");
   FILE *fp_edit_EDF = fopen("edit_EDF.txt", "r");
   FILE *fp_edit_LLF = fopen("edit_LLF.txt", "r");
   FILE *fp_end = fopen("end.txt", "r");
 
   // Open file to store the result
   FILE *fp_final = fopen("final.tex", "w");
   char c;
 
/*   if (fp_begin == NULL || fp_edit == NULL || fp_end == NULL || fp_final == NULL)
   {
         puts("Could not open files");
         exit(0);
   }*/
 
   // Copy contents of first file to .tex file
   while ((c = fgetc(fp_begin)) != EOF)
      fputc(c, fp_final);

   // Copy contents of second file to .tex file
   while ((c = fgetc(fp_edit_RM)) != EOF)
      fputc(c, fp_final);

   // Copy contents of second file to .tex file
   while ((c = fgetc(fp_edit_EDF)) != EOF)
      fputc(c, fp_final);

   // Copy contents of second file to .tex file
   while ((c = fgetc(fp_edit_LLF)) != EOF)
      fputc(c, fp_final);

   // Copy contents of third file to .tex file
   while ((c = fgetc(fp_end)) != EOF)
      fputc(c, fp_final);
 
   printf("Merged file1.txt and file2.txt into final.tex");
 
   fclose(fp_begin);
   fclose(fp_edit_RM);
   fclose(fp_edit_EDF);
   fclose(fp_edit_LLF);
   fclose(fp_end);
   fclose(fp_final);


}
