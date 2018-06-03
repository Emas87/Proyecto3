#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//modo 0 RM
//modo 1 EDF
//modo 2 LLF

void sub_create(int *tasks, int modo, int N_tareas, int mcm_r, int pos_fall, int escala, int filas, int *columnas, int k, int it){

   const char *task_name[6];
   task_name[0] = "T1 ";
   task_name[1] = "T2 ";
   task_name[2] = "T3 ";
   task_name[3] = "T4 ";
   task_name[4] = "T5 ";
   task_name[5] = "T6 ";

   const char *task_color[6];
   task_color[0] = "& \\cellcolor{blue} ";
   task_color[1] = "& \\cellcolor{purple} ";
   task_color[2] = "& \\cellcolor{cyan} ";
   task_color[3] = "& \\cellcolor{gray} ";
   task_color[4] = "& \\cellcolor{yellow} ";
   task_color[5] = "& \\cellcolor{orange} ";

   char show_mode[512];
   FILE *fp_edit;

   if(modo==0){
      fp_edit = fopen("files/FULL_edit_RM.txt", "w");
      strcpy(show_mode,"Rate Monotonic");
   } else if(modo==1){
      fp_edit = fopen("files/FULL_edit_EDF.txt", "w");
      strcpy(show_mode,"Earliest Dead First");
   } else if(modo==2){
      fp_edit = fopen("files/FULL_edit_LLF.txt", "w");
      strcpy(show_mode,"Least Laxity First");
   }

   int i,j,resto;

      fprintf(fp_edit, "%s %s", "\\begin{table}", "\n");
      fprintf(fp_edit, "%s %s", "\\centering", "\n");
      fprintf(fp_edit, "%s %s", "\\resizebox{!}{.07\\linewidth}{", "\n");

      char str[512];
      strcpy(str,"\\begin{tabular}{|l|");
      for(i=0;i<columnas[k+1];i++){
         strcat(str,"l|");
      }
      strcat(str,"}");
      fprintf(fp_edit, "%s %s", str, "\n");

      fprintf(fp_edit, "%s %s", "\\hline", "\n");

      //Status
      fprintf(fp_edit, "%s", "St ");
      for(j=0;j<columnas[k+1];j++){
         if((j==(columnas[k+1]-1)) && (k==it-1) && pos_fall!=0){
            fprintf(fp_edit, "%s", "& \\cellcolor{red} ");
         } else {
            fprintf(fp_edit, "%s", "& \\cellcolor{green} ");
         }
      }
      fprintf(fp_edit, "%s %s %s", "\\\\", "\\hline", "\n");

      //Tasks
      for(i=0;i<filas;i++){
         fprintf(fp_edit, "%s", task_name[i]);
         for(j=0;j<columnas[k+1];j++){
            if(*((tasks+i*mcm_r) + j+(k*24))==0){
               fprintf(fp_edit, "%s", "& ");
            } 
            else if(*((tasks+i*mcm_r) + j+(k*24))==1){
               fprintf(fp_edit, "%s", task_color[i]);
            }
         }
         fprintf(fp_edit, "%s %s %s", "\\\\", "\\hline", "\n");
      }
      
      fprintf(fp_edit, "%s %s", "\\end{tabular}", "\n");
      fprintf(fp_edit, "%s %s", "}", "\n");
      fprintf(fp_edit, "%s %s %d %s %s", "\\caption{", show_mode, k+1, "}", "\n");
      fprintf(fp_edit, "%s %s", "\\end{table}", "\n");


   fclose(fp_edit);

}
