#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sub_create.h"
#include "ecuacion.h"

void wrapper(int *tasks_rm, int *tasks_edf, int *tasks_llf, int modo, int N_tareas, int mcm_r, int pos_fall_rm, int pos_fall_edf, int pos_fall_llf, int escala, int *te, int *p, double miu, double Un){

   FILE *fp_edit = fopen("files/edit_FULL.txt", "w");
   char c;

   if(modo==8){

      ecuacion(0,N_tareas,te,p,miu,Un);//RM
      ecuacion(1,N_tareas,te,p,miu,Un);//EDF
      ecuacion(2,N_tareas,te,p,miu,Un);//LLF

      FILE *fp_exp_RM = fopen("files/exp_RM.txt", "r");
      FILE *fp_exp_EDF = fopen("files/exp_EDF.txt", "r");
      FILE *fp_exp_LLF = fopen("files/exp_LLF.txt", "r");
      FILE *fp_ec_RM = fopen("files/ec_RM.txt", "r");
      FILE *fp_ec_EDF = fopen("files/ec_EDF.txt", "r");
      FILE *fp_ec_LLF = fopen("files/ec_LLF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_LLF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_RM);
      fclose(fp_exp_EDF);
      fclose(fp_exp_LLF);
      fclose(fp_ec_RM);
      fclose(fp_ec_EDF);
      fclose(fp_ec_LLF);

      fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
      fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
      fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
      fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

      sub_create((int*)tasks_rm, 0, N_tareas, mcm_r, pos_fall_rm, escala);//RM
      sub_create((int*)tasks_edf, 1, N_tareas, mcm_r, pos_fall_edf, escala);//EDF
      sub_create((int*)tasks_llf, 2, N_tareas, mcm_r, pos_fall_llf, escala);//LLF

      FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "r");
      FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "r");
      FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);

      fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
      fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   } else if(modo==9){

      ecuacion(1,N_tareas,te,p,miu,Un);//EDF
      ecuacion(2,N_tareas,te,p,miu,Un);//LLF

      FILE *fp_exp_EDF = fopen("files/exp_EDF.txt", "r");
      FILE *fp_exp_LLF = fopen("files/exp_LLF.txt", "r");
      FILE *fp_ec_EDF = fopen("files/ec_EDF.txt", "r");
      FILE *fp_ec_LLF = fopen("files/ec_LLF.txt", "r");

      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_LLF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_EDF);
      fclose(fp_exp_LLF);
      fclose(fp_ec_EDF);
      fclose(fp_ec_LLF);

      fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
      fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
      fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
      fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

      sub_create((int*)tasks_edf, 1, N_tareas, mcm_r, pos_fall_edf, escala);//EDF
      sub_create((int*)tasks_llf, 2, N_tareas, mcm_r, pos_fall_llf, escala);//LLF

      FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "r");
      FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "r");

      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);

      fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
      fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");


   } else if(modo==10){

      ecuacion(0,N_tareas,te,p,miu,Un);//RM
      ecuacion(1,N_tareas,te,p,miu,Un);//EDF

      FILE *fp_exp_RM = fopen("files/exp_RM.txt", "r");
      FILE *fp_exp_EDF = fopen("files/exp_EDF.txt", "r");
      FILE *fp_ec_RM = fopen("files/ec_RM.txt", "r");
      FILE *fp_ec_EDF = fopen("files/ec_EDF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_EDF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_RM);
      fclose(fp_exp_EDF);
      fclose(fp_ec_RM);
      fclose(fp_ec_EDF);

      fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
      fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
      fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
      fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

      sub_create((int*)tasks_rm, 0, N_tareas, mcm_r, pos_fall_rm, escala);//RM
      sub_create((int*)tasks_edf, 1, N_tareas, mcm_r, pos_fall_edf, escala);//EDF

      FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "r");
      FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_EDF)) != EOF)
         fputc(c, fp_edit);

      fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
      fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   } else if(modo==11){

      ecuacion(0,N_tareas,te,p,miu,Un);//RM
      ecuacion(2,N_tareas,te,p,miu,Un);//LLF

      FILE *fp_exp_RM = fopen("files/exp_RM.txt", "r");
      FILE *fp_exp_LLF = fopen("files/exp_LLF.txt", "r");
      FILE *fp_ec_RM = fopen("files/ec_RM.txt", "r");
      FILE *fp_ec_LLF = fopen("files/ec_LLF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_ec_LLF)) != EOF)
         fputc(c, fp_edit);

      fclose(fp_exp_RM);
      fclose(fp_exp_LLF);
      fclose(fp_ec_RM);
      fclose(fp_ec_LLF);

      fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
      fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
      fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
      fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

      sub_create((int*)tasks_rm, 0, N_tareas, mcm_r, pos_fall_rm, escala);//RM
      sub_create((int*)tasks_llf, 2, N_tareas, mcm_r, pos_fall_llf, escala);//LLF

      FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "r");
      FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "r");

      while ((c = fgetc(fp_exp_RM)) != EOF)
         fputc(c, fp_edit);
      while ((c = fgetc(fp_exp_LLF)) != EOF)
         fputc(c, fp_edit);

      fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
      fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   }


   fprintf(fp_edit, "%s %s", "\\subsection{Informacion de Tabla de Tiempo Completa}", "\n");
   fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
   fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
   fprintf(fp_edit, "%s %s", "\\frametitle{Informacion de Tabla de Tiempo Completa}", "\n");
   fprintf(fp_edit, "%s %s", "Informacion General:\\\\", "\n");
   fprintf(fp_edit, "%s %s", "\\begin{itemize}", "\n");
   fprintf(fp_edit, "%s %d %s %s", "\\item Escala Bloque : Ciclos = 1 :", escala, "\\\\", "\n");
   fprintf(fp_edit, "%s %d %s %s", "\\item mcm: ", mcm_r, "\\\\", "\n");
   fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");


   if(modo==8 || modo==10 || modo==11){ //RM
      fprintf(fp_edit, "%s %s", "Informacion de Rate Monotonic:\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\begin{itemize}", "\n");
      fprintf(fp_edit, "%s %d %s %s", "\\item Posicion Fallo: ", pos_fall_rm, "\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");

   } 
   if(modo==8 || modo==9 || modo==10){ //EDF
      fprintf(fp_edit, "%s %s", "Informacion de Earliest Dead First:\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\begin{itemize}", "\n");

      fprintf(fp_edit, "%s %d %s %s", "\\item Posicion Fallo: ", pos_fall_edf, "\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");

   }
   if(modo==8 || modo==9 || modo==11){ //LLF
      fprintf(fp_edit, "%s %s", "Informacion de Least Laxity First:\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\begin{itemize}", "\n");
      fprintf(fp_edit, "%s %d %s %s", "\\item Posicion Fallo: ", pos_fall_llf, "\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");
   }

   fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
   fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   fclose(fp_edit);

}
