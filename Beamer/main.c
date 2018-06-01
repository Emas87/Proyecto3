int main(int argc, char *argv[]){

   system("create");
   system("join");
   system("pdflatex final.tex");
   system("evince final.pdf");
   system("rm *.aux *.log *.nav *.out *.snm *.toc *.vrb");

   return 0;
}
