#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//modo 0 RM
//modo 1 EDF
//modo 2 LLF

void ecuacion(int modo, int N_tareas, int *te, int *p, double miu, double Un){

   const char *task_name[6];
   task_name[0] = "T1 ";
   task_name[1] = "T2 ";
   task_name[2] = "T3 ";
   task_name[3] = "T4 ";
   task_name[4] = "T5 ";
   task_name[5] = "T6 ";

   char show_mode[512];
   FILE *fp_edit;

   if(modo==0){
      fp_edit = fopen("files/ec_RM.txt", "w");
      strcpy(show_mode,"Rate Monotonic");
   } else if(modo==1){
      fp_edit = fopen("files/ec_EDF.txt", "w");
      strcpy(show_mode,"Earliest Dead First");
   } else if(modo==2){
      fp_edit = fopen("files/ec_LLF.txt", "w");
      strcpy(show_mode,"Least Laxity First");
   }

   char c;
   int i,j;
   int filas,columnas[512];

   fprintf(fp_edit, "%s %s %s %s", "\\subsection{Tests de Schedulability ", show_mode ,"}", "\n");
   fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
   fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
   fprintf(fp_edit, "%s %s %s %s", "\\frametitle{Tests de Schedulability ", show_mode ,"}", "\n");
   fprintf(fp_edit, "%s %s", "\\begin{table}", "\n");
   fprintf(fp_edit, "%s %s", "\\centering", "\n");

   char str[512];
   strcpy(str,"\\begin{tabular}{|l|");
   for(i=0;i<2;i++){
      strcat(str,"l|");
   }
   strcat(str,"}");
   fprintf(fp_edit, "%s %s", str, "\n");

   fprintf(fp_edit, "%s %s", "\\hline", "\n");
   fprintf(fp_edit, "%s %s %s %s", "\\cellcolor{lightgray}Tarea & \\cellcolor{lightgray}$P_i$ & \\cellcolor{lightgray}$C_i$", "\\\\", "\\hline", "\n");
   //Tasks
   for(i=0;i<N_tareas;i++){
      fprintf(fp_edit, "%s %s", task_name[i], " & ");
      fprintf(fp_edit, "%d %s %d", p[i], " & ", te[i]);
      fprintf(fp_edit, "%s %s %s", "\\\\", "\\hline", "\n");
   }
      
   fprintf(fp_edit, "%s %s", "\\end{tabular}", "\n");
   fprintf(fp_edit, "%s %s %s %s", "\\caption{Datos ", show_mode,"}", "\n");
   fprintf(fp_edit, "%s %s", "\\end{table}", "\n");

   if(modo==0){//RM
      fprintf(fp_edit, "%s %s %s", "Condicion: $\\mu \\leq U(n)$", "\\\\", "\n");
      fprintf(fp_edit, "%s %f %s %s", "$\\mu = ", miu, "$ \\\\", "\n");
      fprintf(fp_edit, "%s %f %s %s", "$U(n) = ", Un, "$ \\\\", "\n");
      if(miu<=Un){
         fprintf(fp_edit, "%s %s %s","Dado que $\\mu \\leq U(n)$ el algoritmo indica que las tareas si son schedulable", "\\\\", "\n");
      } else {
         fprintf(fp_edit, "%s %s %s","Dado que $\\mu>U(n)$ el algoritmo indica que las tareas no son schedulable", "\\\\", "\n");
      }
   } else if(modo==1){//EDF
      fprintf(fp_edit, "%s %s %s", "Condicion: $\\mu \\leq 1$", "\\\\", "\n");
      fprintf(fp_edit, "%s %f %s %s", "$\\mu = ", miu, "$ \\\\", "\n");
      if(miu<=1.0){
         fprintf(fp_edit, "%s %s %s","Dado que $\\mu \\leq 1$ el algoritmo indica que las tareas si son schedulable", "\\\\", "\n");
      } else {
         fprintf(fp_edit, "%s %s %s","Dado que $\\mu>1$ el algoritmo indica que las tareas no son schedulable", "\\\\", "\n");
      }

   } else if(modo==2){//LLF
      fprintf(fp_edit, "%s %f %s %s", "$\\mu = ", miu, "$ \\\\", "\n");
      fprintf(fp_edit, "%s %f %s %s", "$U(n) = ", Un, "$ \\\\", "\n");

   }

   fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
   fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   

   fclose(fp_edit);

}
