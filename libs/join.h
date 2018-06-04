#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function joins all the info from the files into the final .tex file
void join(){

   // Files are opened to read
   FILE *fp_begin = fopen("files/begin.txt", "r");
   FILE *fp_edit_RM = fopen("files/edit_RM.txt", "r");
   FILE *fp_edit_EDF = fopen("files/edit_EDF.txt", "r");
   FILE *fp_edit_LLF = fopen("files/edit_LLF.txt", "r");
   FILE *fp_edit_FULL = fopen("files/edit_FULL.txt", "r");
   FILE *fp_end = fopen("files/end.txt", "r");
   
   // New .tex file is created
   FILE *fp_final = fopen("Scheduling_TR.tex", "w");
   char c;
 
   // This block joins all the files into the .tex file
   while ((c = fgetc(fp_begin)) != EOF)
      fputc(c, fp_final);

   while ((c = fgetc(fp_edit_RM)) != EOF)
      fputc(c, fp_final);

   while ((c = fgetc(fp_edit_EDF)) != EOF)
      fputc(c, fp_final);

   while ((c = fgetc(fp_edit_LLF)) != EOF)
      fputc(c, fp_final);

   while ((c = fgetc(fp_edit_FULL)) != EOF)
      fputc(c, fp_final);

   while ((c = fgetc(fp_end)) != EOF)
      fputc(c, fp_final);
 
   // The files are closed
   fclose(fp_begin);
   fclose(fp_edit_RM);
   fclose(fp_edit_EDF);
   fclose(fp_edit_LLF);
   fclose(fp_edit_FULL);
   fclose(fp_end);
   fclose(fp_final);

}
