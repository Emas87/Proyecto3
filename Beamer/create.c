#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

   FILE *fp_edit = fopen("edit.txt", "w");
 
 
   if (fp_edit == NULL)
   {
         puts("Could not open files");
         exit(0);
   }

   fprintf(fp_edit, "%s %s", "\\begin{frame}", "\n");
   fprintf(fp_edit, "%s %s", "\\frametitle{Table}", "\n");
   fprintf(fp_edit, "%s %s", "\\begin{table}", "\n");
   fprintf(fp_edit, "%s %s", "\\centering", "\n");
   fprintf(fp_edit, "%s %s", "\\label{RM2}", "\n");
   fprintf(fp_edit, "%s %s", "\\begin{tabular}{|l|l|l|l|l|l|}", "\n");
   fprintf(fp_edit, "%s %s", "\\hline", "\n");
   fprintf(fp_edit, "%s %s %s", "T1 & \\cellcolor{blue} & \\cellcolor{blue} & & & \\\\", "\\hline", "\n");
   fprintf(fp_edit, "%s %s %s", "T2 & & & \\cellcolor{red}  & \\cellcolor{red} & \\\\", "\\hline", "\n");
   fprintf(fp_edit, "%s %s %s", "T3 & & & & & \\cellcolor{green} \\\\", "\\hline", "\n");
   fprintf(fp_edit, "%s %s", "\\end{tabular}", "\n");
   fprintf(fp_edit, "%s %s", "\\caption{Rate Monotonic}", "\n");
   fprintf(fp_edit, "%s %s", "\\end{table}", "\n");
   fprintf(fp_edit, "%s %s", "\\end{frame}", "\n");

   fclose(fp_edit);

   return 0;

}
