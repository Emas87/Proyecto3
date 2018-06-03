#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clean(){

   FILE *fp_edit_RM = fopen("edit_RM.txt", "w");
   FILE *fp_edit_EDF = fopen("edit_EDF.txt", "w");
   FILE *fp_edit_LLF = fopen("edit_LLF.txt", "w");
   FILE *fp_edit_FULL = fopen("edit_FULL.txt", "w");
   FILE *fp_FULL_edit_RM = fopen("FULL_edit_RM.txt", "w");
   FILE *fp_FULL_edit_EDF = fopen("FULL_edit_EDF.txt", "w");
   FILE *fp_FULL_edit_LLF = fopen("FULL_edit_LLF.txt", "w");
   FILE *fp_ec_RM = fopen("ec_RM.txt", "w");
   FILE *fp_ec_EDF = fopen("ec_EDF.txt", "w");
   FILE *fp_ec_LLF = fopen("ec_LLF.txt", "w");
 
   fclose(fp_edit_RM);
   fclose(fp_edit_EDF);
   fclose(fp_edit_LLF);
   fclose(fp_edit_FULL);
   fclose(fp_FULL_edit_RM);
   fclose(fp_FULL_edit_EDF);
   fclose(fp_FULL_edit_LLF);
   fclose(fp_ec_RM);
   fclose(fp_ec_EDF);
   fclose(fp_ec_LLF);



}
