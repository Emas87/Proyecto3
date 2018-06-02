#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//modo 0 RM
//modo 1 EDF
//modo 2 LLF

void create(int * tasks,int modo,int N_tareas,int mcm_r,int pos_fall,int escala){

/*   int tasks[6][64] = {{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
                       {0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0},
                       {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0},
                       {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
                       {0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0},
                       {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1}};
*/
   int tasks[6][9] = {{1,0,0,0,0,0,0,0,1},
                      {0,1,1,0,0,0,0,0,0},
                      {0,0,0,1,0,0,0,0,0},
                      {0,0,0,0,1,0,0,0,0},
                      {0,0,0,0,0,1,1,0,0},
                      {0,0,0,0,0,0,0,1,0}};


   const char *task_name[6];
   task_name[0] = "T1 ";
   task_name[1] = "T2 ";
   task_name[2] = "T3 ";
   task_name[3] = "T4 ";
   task_name[4] = "T5 ";
   task_name[5] = "T6 ";

   const char *task_color[6];
   task_color[0] = "& \\cellcolor{blue} ";
   task_color[1] = "& \\cellcolor{red} ";
   task_color[2] = "& \\cellcolor{green} ";
   task_color[3] = "& \\cellcolor{gray} ";
   task_color[4] = "& \\cellcolor{yellow} ";
   task_color[5] = "& \\cellcolor{orange} ";

   FILE *fp_edit = fopen("edit.txt", "w");
 
   if (fp_edit == NULL)
   {
         puts("Could not open files");
         exit(0);
   }

   int i,j,k,it,resto;
   size_t tasks_s = sizeof(tasks[0])/sizeof(tasks[0][0]);
   size_t tasks_a = sizeof(tasks)/sizeof(tasks[0]);
   int filas,columnas[512];

   if(tasks_s>24){

      it = tasks_s/24 + 1;
      resto = tasks_s%24;

      filas = tasks_a;

      for(i=1;i<it;i++){
         columnas[i] = 24;  
      }
      
      columnas[it] = resto; 
     
   }
   else if(tasks_s<=24){
      it = 1;
      filas = tasks_a;
      columnas[it] = tasks_s;
   }

   for(k=0;k<it;k++) {

      fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
      fprintf(fp_edit, "%s %s", "\\frametitle{Table}", "\n");
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
      

      for(i=0;i<filas;i++){
         fprintf(fp_edit, "%s", task_name[i]);
         for(j=0;j<columnas[k+1];j++){
            if(tasks[i][j]==0){
               fprintf(fp_edit, "%s", "& ");
            } 
            else if(tasks[i][j]==1){
               fprintf(fp_edit, "%s", task_color[i]);
            }
         }
         fprintf(fp_edit, "%s %s %s", "\\\\", "\\hline", "\n");
      }

      fprintf(fp_edit, "%s %s", "\\end{tabular}", "\n");
      fprintf(fp_edit, "%s %s", "\\caption{Rate Monotonic}", "\n");
      fprintf(fp_edit, "%s %s", "\\end{table}", "\n");
      fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");

   }

   fclose(fp_edit);

}
