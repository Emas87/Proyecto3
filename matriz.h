#include <ctype.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
struct matrixs{
   int *rm;
   int *edf;
   int *llf;
} matrixs;

gint grab_int_value (GtkSpinButton *button, gpointer user_data){
   return gtk_spin_button_get_value_as_int (button);
}

//  Recursive function to return gcd of a and b
int gcd(int a, int b)
{
    // base case
    if (a == b)
        return a;
    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}
// Function to return LCM of two numbers
int mcm(int a, int b){
    return (a*b)/gcd(a, b);
}
void RM(int N_tareas,int *p,int *te,int mcm_r,int *output){

   int cola_ready[N_tareas];
   int remaining[N_tareas];
   int tiempo = 0;
   //Ordenarlos por orden de prioridad 1/p[i]
   int aux = 0;
   for(int i = 1; i < N_tareas; i++){
      for(int j = 0; j < (N_tareas - i); ++j){
         if(p[j] > p[j+1]){
            aux = p[j];
            p[j] = p[j + 1];
            p[j + 1] = aux;
            aux = te[j];
            te[j] = te[j + 1];
            te[j + 1] = aux;           
         }
      }
   }
   while(tiempo != mcm_r){
      for(int i = 0; i < N_tareas; i++){//Ver si se cumple el periodo de una tarea, porque eso significa entra a la cola
         if(tiempo % p[i] == 0){
            cola_ready[i] = 1;
            remaining[i] = te[i];
         }
      }
      for(int i = 0; i < N_tareas; i++){//Se llena un campo de la matriz

         if(cola_ready[i] == 1){
            *((output+i*mcm_r) + tiempo) = 1;//se llena la posicion [i][tiempo]
            //output[i][tiempo] = 1;
            remaining[i]--;
            if(remaining[i] == 0){
               cola_ready[i] = 0;
            }
            break;
         }
      }
      tiempo++;
   }
}
void LLF(int N_tareas,int *p,int *te,int mcm_r,int *output){
   int cola_ready[N_tareas];
   int remaining[N_tareas];
   int tiempo = 0;
   int laxity[N_tareas];
   //Ordenarlos por orden de prioridad laxity=p[i]-te[i]
   for(int i = 0; i < N_tareas; i++){//Se llena un campo de la matriz
      laxity[i]=p[i]-te[i];
   }
   int aux = 0;
   for(int i = 1; i < N_tareas; i++){
      for(int j = 0; j < (N_tareas - i); ++j){
         if(laxity[j] > laxity[j+1]){
            aux = p[j];
            p[j] = p[j + 1];
            p[j + 1] = aux;
            aux = te[j];
            te[j] = te[j + 1];
            te[j + 1] = aux;
            aux = laxity[j];
            laxity[j] = laxity[j + 1];
            laxity[j + 1] = aux;
         }
      }
   }
   while(tiempo != mcm_r){
      for(int i = 0; i < N_tareas; i++){//Ver si se cumple el periodo de una tarea, porque eso significa entra a la cola
         if(tiempo % p[i] == 0){
            cola_ready[i] = 1;
            remaining[i] = te[i];
         }
      }
      for(int i = 0; i < N_tareas; i++){//Se llena un campo de la matriz
         if(cola_ready[i] == 1){
            *((output+i*mcm_r) + tiempo) = 1;//se llena la posicion [i][tiempo]
            //output[i][tiempo] = 1;
            remaining[i]--;
            if(remaining[i] == 0){
               cola_ready[i] = 0;
            }
            break;
         }
      }
      tiempo++;
   }
}

void EDF(int N_tareas,int *p,int *te,int mcm_r,int *output){
   int cola_ready[N_tareas];
   int remaining[N_tareas];
   int tiempo = 0;
   int earliest_deadline=mcm_r;
   int next = 0;
   int remain_deadline[N_tareas];
   for(int i = 0; i < N_tareas; i++){//inicializar los proximos deadlines
      remain_deadline[i] = 0;
   }
   while(tiempo != mcm_r){
      for(int i = 0; i < N_tareas; i++){
         if(tiempo % p[i] == 0){//Ver si se cumple el periodo de una tarea, porque eso significa entra a la cola de ready
            cola_ready[i] = 1;
            remaining[i] = te[i];
            remain_deadline[i] += p[i];
         }
         //Se calcula el deadline para ver cual tarea sigue
         if((remain_deadline[i] < earliest_deadline) && cola_ready[i] == 1){
            earliest_deadline = remain_deadline[i];
            next = i;
         }
      }
      *((output+next*mcm_r) + tiempo) = 1;//se llena la posicion [next][tiempo]
      remaining[next]--;
      if(remaining[next] == 0){
         cola_ready[next] = 0;
         earliest_deadline = mcm_r;
      }
      tiempo++;
   }
}
void CrearMatriz(int caso,int N_tareas,int *p,int *te){
   struct matrixs output;
   int mcm_r = 1;//minimo comun multiplo resultado
   for(int i = 0;i<N_tareas;i++){
      mcm_r = mcm(mcm_r,p[i]);
   }
   int output_rm[N_tareas][mcm_r];
   memset(output_rm, 0, sizeof output_rm );
   int output_edf[N_tareas][mcm_r];
   memset(output_edf, 0, sizeof output_edf );
   int output_llf[N_tareas][mcm_r];
   memset(output_llf, 0, sizeof output_llf );


   printf("minimo comun multiplo es: %d\n",mcm_r);

   switch(caso){
      case 1:
         RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
      break;
      case 2:
         EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
         LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
      break;
      case 3:
         RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
      break;
      case 4:
         RM(N_tareas,p,te,mcm_r,(int*)output_rm);
         LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
      break;
      case 5:
         RM(N_tareas,p,te,mcm_r,(int*)output_rm);
      break;      
      case 6:
         EDF(N_tareas,p,te,mcm_r,(int*)output_edf);
      break;
      case 7:
         LLF(N_tareas,p,te,mcm_r,(int*)output_llf);
      break;     
   }
   printf("output = {\n");
   for(int i = 0; i < N_tareas; i++){
      for(int j = 0; j < mcm_r; j++){
         printf("%d ",output_edf[i][j]);
      }
      printf("\n");
   }
   printf("}\n");

   //gtk_main_quit();
}
int isNumericString(const gchar *s){
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

