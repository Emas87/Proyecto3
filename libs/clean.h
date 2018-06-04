#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function erases all the information in the files
// If the file does not exist, it will be created
void clean(){

   // Opening files
   FILE *fp_edit_RM = fopen("files/edit_RM.txt", "w");
   FILE *fp_edit_EDF = fopen("files/edit_EDF.txt", "w");
   FILE *fp_edit_LLF = fopen("files/edit_LLF.txt", "w");
   FILE *fp_edit_FULL = fopen("files/edit_FULL.txt", "w");
   FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "w");
   FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "w");
   FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "w");
   FILE *fp_ec_RM = fopen("files/ec_RM.txt", "w");
   FILE *fp_ec_EDF = fopen("files/ec_EDF.txt", "w");
   FILE *fp_ec_LLF = fopen("files/ec_LLF.txt", "w");
 
   // Closing files
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
