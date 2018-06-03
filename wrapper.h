#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sub_create.h"

void wrapper(int *tasks_rm, int *tasks_edf, int *tasks_llf, int modo, int N_tareas, int mcm_r, int pos_fall_rm, int pos_fall_edf, int pos_fall_llf, int escala){

   char file[512];

   strcpy(file,"edit_FULL.txt");
   FILE *fp_edit = fopen(file, "w");
   char c;

   if(modo==8){

      FILE *fp_exp_RM = fopen("exp_RM.txt", "r");
      FILE *fp_exp_EDF = fopen("exp_EDF.txt", "r");
      FILE *fp_exp_LLF = fopen("exp_LLF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_RM);
      fclose(fp_exp_EDF);
      fclose(fp_exp_LLF);

   } else if(modo==9){

      FILE *fp_exp_EDF = fopen("exp_EDF.txt", "r");
      FILE *fp_exp_LLF = fopen("exp_LLF.txt", "r");

      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_EDF);
      fclose(fp_exp_LLF);

   } else if(modo==10){

      FILE *fp_exp_RM = fopen("exp_RM.txt", "r");
      FILE *fp_exp_EDF = fopen("exp_EDF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_RM);
      fclose(fp_exp_EDF);

   } else if(modo==11){

      FILE *fp_exp_RM = fopen("exp_RM.txt", "r");
      FILE *fp_exp_LLF = fopen("exp_LLF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_RM);
      fclose(fp_exp_LLF);

   }

   fclose(fp_edit);

}
