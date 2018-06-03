#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sub_create.h"
#include "ecuacion.h"

int positions(int N_tareas, int mcm_r, int pos_fall, int *filas, int * columnas, int *it){

   int i,resto;

   if(mcm_r>24){

      if(pos_fall==0){
         resto = mcm_r%24;
         if(resto==0){
            *it = mcm_r/24;
            for(i=1;i<=*it;i++){
               columnas[i] = 24;
            }
         } else {
            *it = mcm_r/24 + 1;
            for(i=1;i<*it;i++){
               columnas[i] = 24;
            }
            columnas[*it] = resto;
         }
      } else {
         if(pos_fall>24){
            resto = pos_fall%24;
            if(resto==0){
               *it = pos_fall/24;
               for(i=1;i<=*it;i++){
                  columnas[i] = 24;
               }
            } else {
               *it = pos_fall/24 + 1;
               for(i=1;i<*it;i++){
                  columnas[i] = 24;
               }
               columnas[*it] = resto+1;
            }
         } else {
            *it = 1;
            columnas[*it] = pos_fall+1;
         }
      }
      *filas = N_tareas;
   }
   else if(mcm_r<=24){
      *it = 1;
      *filas = N_tareas;
      if(pos_fall==0){
         columnas[*it] = mcm_r;
      } else {
         columnas[*it] = pos_fall+1;
      }
   }

}

void wrapper(int *tasks_rm, int *tasks_edf, int *tasks_llf, int modo, int N_tareas, int mcm_r, int pos_fall_rm, int pos_fall_edf, int pos_fall_llf, int escala, int *te, int *p, double miu, double Un){

   FILE *fp_edit = fopen("files/edit_FULL.txt", "w");
   char c;
   int k,it;

   int filas, columnas_RM[512], it_RM, columnas_EDF[512], it_EDF, columnas_LLF[512], it_LLF;

   positions(N_tareas, mcm_r, pos_fall_rm, &filas, (int*)&columnas_RM, &it_RM);
   positions(N_tareas, mcm_r, pos_fall_edf, &filas, (int*)&columnas_EDF, &it_EDF);
   positions(N_tareas, mcm_r, pos_fall_llf, &filas, (int*)&columnas_LLF, &it_LLF);

   if(it_RM>=it_EDF && it_RM>=it_LLF){
      it = it_RM;
   } else 
   if(it_EDF>=it_RM && it_EDF>=it_LLF){
      it = it_EDF;
   } else 
   if(it_LLF>=it_RM && it_LLF>=it_EDF){
      it = it_RM;
   }  

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

      for(k=0;k<it;k++) {

         fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
         fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
         fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
         fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

         if(k<it_RM){
            sub_create((int*)tasks_rm, 0, N_tareas, mcm_r, pos_fall_rm, escala, filas, (int*)columnas_RM, k, it_RM);//RM
         }
         if(k<it_EDF){
            sub_create((int*)tasks_edf, 1, N_tareas, mcm_r, pos_fall_edf, escala, filas, (int*)columnas_EDF, k, it_EDF);//EDF
         }
         if(k<it_LLF){
            sub_create((int*)tasks_llf, 2, N_tareas, mcm_r, pos_fall_llf, escala, filas, (int*)columnas_LLF, k, it_LLF);//LLF
         }

         FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "r");
         FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "r");
         FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "r");

         while ((c = fgetc(fp_FULL_edit_RM)) != EOF)
            fputc(c, fp_edit);
         while ((c = fgetc(fp_FULL_edit_EDF)) != EOF)
            fputc(c, fp_edit);
         while ((c = fgetc(fp_FULL_edit_LLF)) != EOF)
            fputc(c, fp_edit);

         fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
         fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

      }

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

      for(k=0;k<it;k++) {

         fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
         fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
         fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
         fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

         if(k<it_EDF){
            sub_create((int*)tasks_edf, 1, N_tareas, mcm_r, pos_fall_edf, escala, filas, (int*)columnas_EDF, k, it_EDF);//EDF
         }
         if(k<it_LLF){
            sub_create((int*)tasks_llf, 2, N_tareas, mcm_r, pos_fall_llf, escala, filas, (int*)columnas_LLF, k, it_LLF);//LLF
         }

         FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "r");
         FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "r");

         while ((c = fgetc(fp_FULL_edit_EDF)) != EOF)
            fputc(c, fp_edit);
         while ((c = fgetc(fp_FULL_edit_LLF)) != EOF)
            fputc(c, fp_edit);

         fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
         fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

      }

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

      for(k=0;k<it;k++) {

         fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
         fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
         fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
         fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

         if(k<it_RM){
            sub_create((int*)tasks_rm, 0, N_tareas, mcm_r, pos_fall_rm, escala, filas, (int*)columnas_RM, k, it_RM);//RM
         }
         if(k<it_EDF){
            sub_create((int*)tasks_edf, 1, N_tareas, mcm_r, pos_fall_edf, escala, filas, (int*)columnas_EDF, k, it_EDF);//EDF
         }

         FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "r");
         FILE *fp_FULL_edit_EDF = fopen("files/FULL_edit_EDF.txt", "r");

         while ((c = fgetc(fp_FULL_edit_RM)) != EOF)
            fputc(c, fp_edit);
         while ((c = fgetc(fp_FULL_edit_EDF)) != EOF)
            fputc(c, fp_edit);

         fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
         fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

      }

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

      for(k=0;k<it;k++) {

         fprintf(fp_edit, "%s %s", "\\subsection{Tabla de Tiempo Completa}", "\n");
         fprintf(fp_edit, "%s","\n%------------------------------------------------\n");
         fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
         fprintf(fp_edit, "%s %s", "\\frametitle{Tabla de Tiempo Completa}", "\n");

         if(k<it_RM){
            sub_create((int*)tasks_rm, 0, N_tareas, mcm_r, pos_fall_rm, escala, filas, (int*)columnas_RM, k, it_RM);//RM
         }
         if(k<it_LLF){
            sub_create((int*)tasks_llf, 2, N_tareas, mcm_r, pos_fall_llf, escala, filas, (int*)columnas_LLF, k, it_LLF);//LLF
         }

         FILE *fp_FULL_edit_RM = fopen("files/FULL_edit_RM.txt", "r");
         FILE *fp_FULL_edit_LLF = fopen("files/FULL_edit_LLF.txt", "r");

         while ((c = fgetc(fp_FULL_edit_RM)) != EOF)
            fputc(c, fp_edit);
         while ((c = fgetc(fp_FULL_edit_LLF)) != EOF)
            fputc(c, fp_edit);

         fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
         fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

      }

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
      if(pos_fall_rm==0){
         fprintf(fp_edit, "%s %s %s", "\\item Posicion Fallo: No hay ningun fallo", "\\\\", "\n");
      } else {
         fprintf(fp_edit, "%s %d %s %s", "\\item Posicion Fallo: ", pos_fall_rm+1, "\\\\", "\n");
      }
      fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");

   } 
   if(modo==8 || modo==9 || modo==10){ //EDF
      fprintf(fp_edit, "%s %s", "Informacion de Earliest Dead First:\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\begin{itemize}", "\n");
      if(pos_fall_edf==0){
         fprintf(fp_edit, "%s %s %s", "\\item Posicion Fallo: No hay ningun fallo", "\\\\", "\n");
      } else {
         fprintf(fp_edit, "%s %d %s %s", "\\item Posicion Fallo: ", pos_fall_edf+1, "\\\\", "\n");
      }
      fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");

   }
   if(modo==8 || modo==9 || modo==11){ //LLF
      fprintf(fp_edit, "%s %s", "Informacion de Least Laxity First:\\\\", "\n");
      fprintf(fp_edit, "%s %s", "\\begin{itemize}", "\n");
      if(pos_fall_llf==0){
         fprintf(fp_edit, "%s %s %s", "\\item Posicion Fallo: No hay ningun fallo", "\\\\", "\n");
      } else {
         fprintf(fp_edit, "%s %d %s %s", "\\item Posicion Fallo: ", pos_fall_llf+1, "\\\\", "\n");
      }
      fprintf(fp_edit, "%s %s", "\\end{itemize}", "\n");
   }

   fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");
   fprintf(fp_edit, "%s", "\n%------------------------------------------------\n");

   fclose(fp_edit);

}
