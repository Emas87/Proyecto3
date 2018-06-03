#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean(){

   FILE *fp_edit_RM = fopen("edit_RM.txt", "w");
   FILE *fp_edit_EDF = fopen("edit_EDF.txt", "w");
   FILE *fp_edit_LLF = fopen("edit_LLF.txt", "w");
   FILE *fp_edit_FULL = fopen("edit_FULL.txt", "w");
 
   fclose(fp_edit_RM);
   fclose(fp_edit_EDF);
   fclose(fp_edit_LLF);
   fclose(fp_edit_FULL);

}
