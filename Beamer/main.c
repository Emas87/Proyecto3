#include <stdlib.h>
#include "create.h"
#include "join.h"

int main(int argc, char *argv[]){

   create();
   join();
   system("pdflatex final.tex");
   system("evince final.pdf");
   system("rm *.aux *.log *.nav *.out *.snm *.toc *.vrb");

   return 0;
}
