#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//modo 0 RM
//modo 1 EDF
//modo 2 LLF

void create(int *tasks, int modo, int N_tareas, int mcm_r, int pos_fall, int escala){

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

   char file[512];
   char show_mode[512];

   if(modo==0){
      strcpy(file,"edit_RM.txt");
      strcpy(show_mode,"Rate Monotonic");
   } else if(modo==1){
      strcpy(file,"edit_EDF.txt");
      strcpy(show_mode,"Earliest Dead First");
   } else if(modo==2){
      strcpy(file,"edit_LLF.txt");
      strcpy(show_mode,"Least Laxity First");
   }

   FILE *fp_edit = fopen(file, "w");
   char c;

   if(modo==0){
      FILE *fp_exp_RM = fopen("exp_RM.txt", "r");
      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      fclose(fp_exp_RM);

      FILE *fp_ec_RM = fopen("ec_RM.txt", "r");
      while ((c = fgetc(fp_ec_RM)) != EOF)
         fputc(c, fp_edit);
      fclose(fp_ec_RM);

   } else if(modo==1){
      FILE *fp_exp_EDF = fopen("exp_EDF.txt", "r");
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      fclose(fp_exp_EDF);

      FILE *fp_ec_EDF = fopen("ec_EDF.txt", "r");
      while ((c = fgetc(fp_ec_EDF)) != EOF)
         fputc(c, fp_edit);
      fclose(fp_ec_EDF);

   } else if(modo==2){
      FILE *fp_exp_LLF = fopen("exp_LLF.txt", "r");
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);
      fclose(fp_exp_LLF);

      FILE *fp_ec_LLF = fopen("ec_LLF.txt", "r");
      while ((c = fgetc(fp_ec_LLF)) != EOF)
         fputc(c, fp_edit);
      fclose(fp_ec_LLF);

   }

   int i,j,k,it,resto;
   int filas,columnas[512];

   if(mcm_r>24){

      if(pos_fall==0){
         resto = mcm_r%24;
         if(resto==0){
            it = mcm_r/24;
            for(i=1;i<=it;i++){
               columnas[i] = 24;
            }
         } else {
            it = mcm_r/24 + 1;
            for(i=1;i<it;i++){
               columnas[i] = 24;
            }
            columnas[it] = resto;
         }
      } else {
         if(pos_fall>24){
            resto = pos_fall%24;
            if(resto==0){
               it = pos_fall/24;
               for(i=1;i<=it;i++){
                  columnas[i] = 24;
               }
            } else {
               it = pos_fall/24 + 1;
               for(i=1;i<it;i++){
                  columnas[i] = 24;
               }
               columnas[it] = resto+1;
            }
         } else {
            it = 1;
            columnas[it] = pos_fall+1;
         }
      }
      filas = N_tareas;
   }
   else if(mcm_r<=24){
      it = 1;
      filas = N_tareas;
      if(pos_fall==0){
         columnas[it] = mcm_r;
      } else {
         columnas[it] = pos_fall+1;
      }
   }

   fprintf(fp_edit, "%s %s %s %s", "\\subsection{Tabla de Tiempo ", show_mode ,"}", "\n");

   for(k=0;k<it;k++) {

      fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
      fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
      fprintf(fp_edit, "%s %s %s %s", "\\frametitle{Tabla de Tiempo ", show_mode ,"}", "\n");
      fprintf(fp_edit, "%s %s", "\\begin{table}", "\n");
      fprintf(fp_edit, "%s %s", "\\centering", "\n");

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
      fprintf(fp_edit, "%s %s %d %s %s", "\\caption{", show_mode, k+1, "}", "\n");
      fprintf(fp_edit, "%s %s", "\\end{table}", "\n");
      fprintf(fp_edit, "%s %d %s %s", "Escala Bloque : Ciclos = 1 :", escala, "\\\\", "\n");
      fprintf(fp_edit, "%s %d %s %s", "Posicion Fallo: ", pos_fall, "\\\\", "\n");
      fprintf(fp_edit, "%s %d %s %s", "mcm: ", mcm_r, "\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
      fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   }

   fclose(fp_edit);

}
