#include <ctype.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <math.h>
#include "wrapper.h"
#include "create.h"
#include "join.h"
#include "clean.h"

gint grab_int_value (GtkSpinButton *button, gpointer user_data){
   return gtk_spin_button_get_value_as_int (button);
}

//  Funcion recursiva que devuelve el maximo comun divisor de a y b
int mcd(int a, int b)
{
    // caso base
    if (a == b)
        return a;
    // a es mayor
    if (a > b)
        return mcd(a-b, b);
    return mcd(a, b-a);
}
// Funcion que devueleve el minimo comun multiplo de 2 numeros
int mcm(int a, int b){
    return (a*b)/mcd(a, b);
}
int RM(int N_tareas,int *p,int *te,int mcm_r,int *output){
   int cola_ready[N_tareas];
   int remaining[N_tareas];
   int orden[N_tareas];
   int tiempo = 0;
   int pos_f = 0;//posicion donde falla

   //Ordenarlos por orden de prioridad 1/p[i]
   for(int i = 0; i < N_tareas; i++){
      orden[i] = i;
   }

   int aux = 0;
   for(int i = 1; i < N_tareas; i++){//orden tiene el orden en que se va a revisar las prioridades
      for(int j = 0; j < (N_tareas - i); ++j){
         if(p[orden[j]] > p[orden[j]+1]){
            aux = orden[j];
            orden[j] = orden[j + 1];
            orden[j + 1] = aux;  
         }
      }
   }
   while(tiempo <= mcm_r){
      for(int i = 0; i < N_tareas; i++){
         if(tiempo != 0 && tiempo % p[orden[i]] == 0 && remaining[orden[i]]>0){//Se verifica si alguna tarea perdio el deadline
            pos_f = tiempo;
         }
         //Ver si se cumple el periodo de una tarea, porque eso significa entra a la cola
         if(tiempo % p[orden[i]] == 0){
            cola_ready[orden[i]] = 1;
            remaining[orden[i]] = te[orden[i]];
         }
      }
      for(int i = 0; i < N_tareas; i++){//Se llena un campo de la matriz
         if(tiempo == mcm_r){
            break;
         }
         if(cola_ready[orden[i]] == 1){
            (output[orden[i]*mcm_r + tiempo]) = 1;//se llena la posicion [orden[i]][tiempo]
            remaining[orden[i]]--;
            if(remaining[orden[i]] == 0){
               cola_ready[orden[i]] = 0;
            }
            break;
         }
      }
      if(pos_f == tiempo && tiempo != 0){//Hubo una falla
         tiempo = mcm_r;
      }
      tiempo++;
   }
   return pos_f;
}

int LLF(int N_tareas,int *p,int *te,int mcm_r,int *output){
   int cola_ready[N_tareas];
   int remaining[N_tareas];
   int tiempo = 0;
   int laxity[N_tareas];   
   int least_laxity=mcm_r;//Se inicia el least lexity para que se calcule en el proximo ciclo
   int next = 0;
   int remain_deadline[N_tareas];
   int pos_f = 0;//posicion donde falla
   for(int i = 0; i < N_tareas; i++){//inicializar los proximos deadlines
      remain_deadline[i] = 0;
   }
   while(tiempo <= mcm_r){
      for(int i = 0; i < N_tareas; i++){
         //Se verifica si alguna trea perdio el deadline
         if(tiempo != 0 && tiempo % p[i] == 0 && remaining[i]>0){
            pos_f = tiempo;
         }
         //Ver si se cumple el periodo de una tarea, porque eso significa entra a la cola de ready
         if(tiempo % p[i] == 0){
            cola_ready[i] = 1;
            remaining[i] = te[i];
            remain_deadline[i] += p[i];
         }
         //Calcular laxity de cada ciclo de tiempo para ver cual tarea sigue
         laxity[i]=remain_deadline[i]-remaining[i]-tiempo;
         if((laxity[i] <= least_laxity) && cola_ready[i] == 1){
               least_laxity = laxity[i];
               next = i;
         }
      }
      if(tiempo != mcm_r){
         (output[next*mcm_r + tiempo]) = cola_ready[next];//se llena la posicion [next][tiempo]
      }
      remaining[next]--;
      if(remaining[next] == 0){
         cola_ready[next] = 0;
      }
      least_laxity = mcm_r;//Se resetea el least lexity para que se calcule en el proximo ciclo 
      if(pos_f == tiempo && tiempo != 0){//Hubo una falla
         tiempo = mcm_r;
      }
      tiempo++;
   }
   return pos_f;
}
int EDF(int N_tareas,int *p,int *te,int mcm_r,int *output){
   int cola_ready[N_tareas];
   int remaining[N_tareas];
   int tiempo = 0;
   int earliest_deadline=mcm_r;
   int next = 0;
   int remain_deadline[N_tareas];
   int pos_f = 0;//posicion donde falla
   for(int i = 0; i < N_tareas; i++){//inicializar los proximos deadlines
      remain_deadline[i] = 0;
   }
   while(tiempo <= mcm_r){
      for(int i = 0; i < N_tareas; i++){
         if(tiempo != 0 && tiempo % p[i] == 0 && remaining[i]>0){//Se verifica si alguna trea perdio el deadline
            pos_f = tiempo;
         }
         if(tiempo % p[i] == 0){//Ver si se cumple el periodo de una tarea, porque eso significa entra a la cola de ready
            cola_ready[i] = 1;
            remaining[i] = te[i];
            remain_deadline[i] += p[i];
            //Se calcula el deadline para ver cual tarea sigue
            if((remain_deadline[i] <= earliest_deadline) && cola_ready[i] == 1){
               earliest_deadline = remain_deadline[i];
               next = i;
            }
         }
      }
      if(tiempo != mcm_r){      
         (output[next*mcm_r + tiempo]) = cola_ready[next];//se llena la posicion [next][tiempo]
      }
      remaining[next]--;
      if(remaining[next] == 0){
         cola_ready[next] = 0;
         earliest_deadline = mcm_r;
         for(int i = 0; i < N_tareas; i++){
            //Se calcula el deadline para ver cual tarea sigue            
            if((remain_deadline[i] <= earliest_deadline) && cola_ready[i] == 1){
               earliest_deadline = remain_deadline[i];
               next = i;
            }
         }
         
      }
      if(pos_f == tiempo && tiempo != 0){//Hubo una falla
         tiempo = mcm_r;
      }
      tiempo++;
   }
   return pos_f;
}
//Funcion que imprime matrices en la terminal
void print_matr(int *output_rm,int *output_edf,int *output_llf,int N_tareas,int mcm_r,int pos_f_rm,int pos_f_edf,int pos_f_llf){
   int largo_rm = mcm_r;
   int largo_edf = mcm_r;
   int largo_llf = mcm_r;

   if(pos_f_rm){
      largo_rm = pos_f_rm;
   }
   if(pos_f_edf){
      largo_edf = pos_f_edf;
   }
   if(pos_f_llf){
      largo_llf = pos_f_llf;
   }
   printf("output rm = {\n");
   for(int i = 0; i < N_tareas; i++){
      printf("T%d ",i);
      for(int j = 0; j < largo_rm; j++){
         printf("%d ",*((output_rm+i*mcm_r) + j));
      }
      printf("\n");
   }
   printf("}\n");
   printf("output edf = {\n");
   for(int i = 0; i < N_tareas; i++){
      printf("T%d ",i+1);      
      for(int j = 0; j < largo_edf; j++){
         printf("%d ",*((output_edf+i*mcm_r) + j));
      }
      printf("\n");
   }
   printf("}\n");
   printf("output llf = {\n");
   for(int i = 0; i < N_tareas; i++){
      printf("T%d ",i+1);      
      for(int j = 0; j < largo_llf; j++){
         printf("%d ",*((output_llf+i*mcm_r) + j));
      }
      printf("\n");
   }
   printf("}\n");   
}
void CrearMatriz(int caso,int N_tareas,int *p,int *te){
   float miu,Un;
   int pos_f_rm = 0,pos_f_edf = 0,pos_f_llf = 0;//En caso de falla se guarda la posicion
   int mcm_r = 1;//minimo comun multiplo resultado
   for(int i = 0;i<N_tareas;i++){
      mcm_r = mcm(mcm_r,p[i]);
      miu = 0;
   }
   //La escala va a ser el maximo comun divisor de todos los periodos y los tiempos de ejecucion
   int escala = mcm_r;//se usa el mcm al inicio para que no inlfuya en el maximo comun divisor 
   for(int i = 0;i<N_tareas;i++){
      escala = mcd(escala,p[i]);
   }
   for(int i = 0;i<N_tareas;i++){
      escala = mcd(escala,te[i]);
   }
   //Se calcula el u y U(n)
   Un = (double)N_tareas*(pow((double)2,(double)1/(double)N_tareas)-1);
   for(int i = 0;i<N_tareas;i++){
      miu += (float)te[i]/(float)p[i];
   }
   //Ahora se divide entre la escala
   for(int i = 0;i<N_tareas;i++){
      p[i] = p[i]/escala;
   }
   for(int i = 0;i<N_tareas;i++){
      te[i] = te[i]/escala;
   }
   mcm_r = mcm_r/escala;
   //Se inician todas las matrices con ceros
   int output_rm[N_tareas][mcm_r];
   memset(output_rm, 0, sizeof output_rm );
   int output_edf[N_tareas][mcm_r];
   memset(output_edf, 0, sizeof output_edf );
   int output_llf[N_tareas][mcm_r];
   memset(output_llf, 0, sizeof output_llf );

   int create_mode;
   switch(caso){
      case 1:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;
      case 2:
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;
      case 3:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         create_mode = caso;
      break;
      case 4:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;
      case 5:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         create_mode = caso;
      break;      
      case 6:
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         create_mode = caso;
      break;
      case 7:
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;     
      case 8:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;
      case 9:
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;      
      case 10:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         pos_f_edf = EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         create_mode = caso;
      break;
      case 11:
         pos_f_rm = RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         pos_f_llf = LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
         create_mode = caso;
      break;
   }

   print_matr((int*)output_rm,(int*)output_edf,(int*)output_llf,N_tareas,mcm_r,pos_f_rm,pos_f_edf,pos_f_llf);
   clean();
   //Se crean las tablas en latex
   if(create_mode == 1 || create_mode == 3 || create_mode == 4 || create_mode == 5){
      ecuacion(0,N_tareas,te,p,miu,Un);
      create((int*)output_rm, 0, N_tareas, mcm_r, pos_f_rm, escala);//RM
   } 
   if(create_mode == 1 || create_mode == 2 || create_mode == 3 || create_mode == 6){
      ecuacion(1,N_tareas,te,p,miu,Un);
      create((int*)output_edf, 1, N_tareas, mcm_r, pos_f_edf, escala);//EDF
   } 
   if(create_mode == 1 || create_mode == 2 || create_mode == 4 || create_mode == 7){
      ecuacion(2,N_tareas,te,p,miu,Un);
      create((int*)output_llf, 2, N_tareas, mcm_r, pos_f_llf, escala);//LLF
   }
   if(create_mode >= 8){//Mismo slide
      wrapper((int*)output_rm, (int*)output_edf, (int*)output_llf, create_mode, N_tareas, mcm_r, pos_f_rm, pos_f_edf, pos_f_llf, escala, te, p, miu, Un);
   }

   join();
   FILE *in=NULL;
   //Se crea el pdf final
   system("pdflatex Scheduling_TR.tex > temp.o");
   system("evince Scheduling_TR.pdf & > temp.o");   
   system("rm *.aux *.log *.nav *.out *.snm *.toc > temp.o");      
}
int isNumericString(const gchar *s){//Verifica que string este compuesto solo de numeros enteros
   int i=0, isNumeric = 0, ctDecimalPointsSeen=0;
   while(s[i] != '\0'){
      if (!isdigit(s[i])){         
         isNumeric=0;
         break;
      }
      i += 1;
      isNumeric = 1;
   }
   return isNumeric;
}

