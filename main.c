#include "matriz.h"

void Compute(gpointer context_object){
   GtkWidget *s_button = g_object_get_data (context_object, "s_button");
   const gchar *text;
   char temp[100];
   GtkWidget *entry_t;
   GtkWidget *entry_p; 
   //Crear labels e input widgets
   gint N_tareas = grab_int_value( (gpointer)s_button,"");
   int p[N_tareas],te[N_tareas];
   for(int i = 0;i<N_tareas;i++){
      //Obtener entradas
      sprintf(temp,"entry_t%d",i+1);      
      entry_t = g_object_get_data (context_object, temp); //Entrada Tiempo de Ejecucion
      sprintf(temp,"entry_p%d",i+1);
      entry_p = g_object_get_data (context_object, temp); //Entrada Periodo
      text = gtk_entry_get_text( GTK_ENTRY(entry_t));
      te[i] = atoi(text);
      text = gtk_entry_get_text( GTK_ENTRY(entry_p));
      p[i] = atoi(text);
   }

   GtkWidget *cb_rm = g_object_get_data (context_object, "cb_rm");
   GtkWidget *cb_edf = g_object_get_data (context_object, "cb_edf");
   GtkWidget *cb_llf = g_object_get_data (context_object, "cb_llf");
   int caso=0;
   if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_rm)) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_edf)) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_llf))){
      caso = 1;//Todos los algoritmo solicitados
   } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_edf)) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_llf))){
      caso = 2;//solo EDF y LLF
   } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_rm)) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_edf)) ){
      caso = 3;//solo RM y EDF
   } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_rm)) && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_llf))){
      caso = 4;//solo RM y LLF
   } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_rm))){
      caso = 5;//solo RM
   } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_edf))){
      caso = 6;//Solo EDF
   } else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_llf))){
      caso = 7;//Solo LLF
   }
   CrearMatriz(caso,N_tareas,p,te);
}
void prev_window_A(GtkWidget *widget, gpointer context_object ){
   GtkWidget *prev = g_object_get_data (context_object, "window2");
   GtkWidget *curr = g_object_get_data (context_object, "window3");
	gtk_widget_show(prev);
   gtk_widget_destroy(curr);
}
void prev_window_T(GtkWidget *widget, gpointer context_object ){
   GtkWidget *prev = g_object_get_data (context_object, "window1");
   GtkWidget *curr = g_object_get_data (context_object, "window2");
	gtk_widget_show(prev);
   gtk_widget_destroy(curr);
}

void test_a(GtkWidget *widget, gpointer context_object){//Test Algoritmos
   
   GtkWidget *cb_rm = g_object_get_data (context_object, "cb_rm");
   GtkWidget *cb_edf = g_object_get_data (context_object, "cb_edf");
   GtkWidget *cb_llf = g_object_get_data (context_object, "cb_llf");
   GtkWidget *label_a = g_object_get_data (context_object, "label_a");

   if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_rm)) || gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_edf)) || gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cb_llf))){
      gtk_label_set_text(GTK_LABEL(label_a),"" );      
      Compute(context_object);
   } else {
      gtk_label_set_text(GTK_LABEL(label_a),"Tiene que seleccionar minimo 1 algoritmo" );
   }
   

}
void Algoritmos( gpointer context_object){
   GtkWidget *window3 = NULL;
  	GtkWidget *box = NULL;
   GtkWidget *b_prev = NULL;
   GtkWidget *b_finish = NULL;
   GtkWidget *win_prev = g_object_get_data (context_object, "window2");

   gtk_widget_hide(GTK_WIDGET(win_prev));

   //Crear Ventana
   window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_container_set_border_width (GTK_CONTAINER (window3), 8);
	gtk_window_set_title (GTK_WINDOW (window3), "Tipos de Algoritmos");
	gtk_window_set_position (GTK_WINDOW (window3), GTK_WIN_POS_CENTER);   
	gtk_widget_realize (window3);
   //g_object_set_data (context_object, "prev", win_prev);
   //g_object_set_data (context_object, "curr", window3 );
	//g_signal_connect (window3, "destroy", gtk_main_quit , NULL);

   // Create a box with buttons
	box = gtk_box_new (TRUE, 6);
   gtk_container_add (GTK_CONTAINER (window3), box);

   //Crear los checkboxs
   GtkWidget *cb_rm = gtk_check_button_new_with_label ("RM");
	gtk_box_pack_start (GTK_BOX (box),cb_rm , TRUE, TRUE , 10);
   GtkWidget *cb_edf = gtk_check_button_new_with_label ("EDF");
	gtk_box_pack_start (GTK_BOX (box),cb_edf , TRUE, TRUE , 10);
   GtkWidget *cb_llf = gtk_check_button_new_with_label ("LLF");
	gtk_box_pack_start (GTK_BOX (box),cb_llf , TRUE, TRUE , 10);

	b_prev = gtk_button_new_with_label("Previous");
	b_finish = gtk_button_new_with_label("Finish");

   //g_object_set_data (context_object, "", win_prev);
   g_object_set_data (context_object, "window3", window3);
	g_signal_connect (G_OBJECT (b_prev), "clicked", G_CALLBACK (prev_window_A),context_object );
   g_object_set_data (context_object, "cb_rm",cb_rm );
   g_object_set_data (context_object, "cb_edf",cb_edf );
   g_object_set_data (context_object, "cb_llf",cb_llf );
   GtkWidget *label_a = gtk_label_new(""); //Label que indica si los algoritmos son correctos
   g_object_set_data (context_object, "label_a",label_a);
	g_signal_connect (G_OBJECT (b_finish), "clicked", G_CALLBACK (test_a), context_object );
	gtk_box_pack_start (GTK_BOX (box), label_a, TRUE,TRUE , 10);      
	gtk_box_pack_start (GTK_BOX (box), b_prev, TRUE, TRUE, 10);
	gtk_box_pack_start (GTK_BOX (box), b_finish, TRUE,TRUE , 10);
	gtk_widget_show_all (window3);
}
int test_e(GtkWidget *widget, gpointer context_object){//Test Entradas
   GtkWidget *s_button = g_object_get_data (context_object, "s_button");
   GtkWidget *label = g_object_get_data (context_object, "label_c");

   //Crear labels e input widgets
   gint N_tareas = grab_int_value( (gpointer)s_button,"");

   const gchar *text;
   char error[100],temp[100];
   int te = 0; //Tiempo de ejecucion
   int p = 0;  //Periodo
   GtkWidget *entry_t;
   GtkWidget *entry_p; 
   for(int i = 0;i<N_tareas;i++){
      //Obtener entradas
      sprintf(temp,"entry_t%d",i+1);      
      entry_t = g_object_get_data (context_object, temp); //Entrada Tiempo de Ejecucion
      sprintf(temp,"entry_p%d",i+1);
      entry_p = g_object_get_data (context_object, temp); //Entrada Periodo

      text = gtk_entry_get_text( GTK_ENTRY(entry_t));
      if(!isNumericString(text)){
         sprintf(error,"Caracter invalido en tiempo de ejecucion de Tarea %d, solo se aceptan numeros enteros",i+1);
         gtk_label_set_text(GTK_LABEL(label),error);
         return -1;
      }
      te = atoi(text);
      text = gtk_entry_get_text( GTK_ENTRY(entry_p));

      if(!isNumericString(text)){
         sprintf(error,"Caracter invalido en el periodo de Tarea %d, solo se aceptan numeros enteros",i+1);
         gtk_label_set_text(GTK_LABEL(label),error);
         return -1;
      }
      p = atoi(text);
      if(te > p){//Si el tiempo de ejecucion es mayor al periodo
         sprintf(error,"El tiempo de ejecucion de la Tarea %d es mayor que el periodo, debe ser menor o igual",i+1);
         gtk_label_set_text(GTK_LABEL(label),error);
         return -1;
      }
      gtk_label_set_text(GTK_LABEL(label),"");
   }
   Algoritmos(context_object);
}
void sure(GtkWidget *widget,gpointer context_object)
{
   GtkWidget *dialog = NULL;
   GtkWidget *curr = g_object_get_data (context_object, "curr");
   dialog = gtk_message_dialog_new (GTK_WINDOW (curr), GTK_DIALOG_MODAL , GTK_MESSAGE_QUESTION , GTK_BUTTONS_YES_NO, "Esta seguro que quiere salir?");
   //dialog = gtk_message_dialog_new (GTK_WINDOW (curr), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
   gtk_window_set_title(GTK_WINDOW(dialog), "Salir?");
   gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
   if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_YES){
      gtk_main_quit();
   }
   gtk_widget_destroy(dialog);
	gtk_widget_show(curr);
}
GtkWidget* create_integer_spin_button (void){
   GtkWidget *window, *button;
   GtkAdjustment *adjustment;
   adjustment = gtk_adjustment_new (1, 1, 6, 1, 1, 0);
   button = gtk_spin_button_new (adjustment, 1, 0);
   return button;
}
void Ejec_Per (GtkWidget *wid,gpointer context_object){
   GtkWidget *window2 = NULL;
  	GtkWidget *box = NULL;
   GtkWidget *b_next = NULL;
   GtkWidget *b_prev = NULL;
   GtkWidget *s_button = g_object_get_data (context_object, "s_button");
   GtkWidget *win = g_object_get_data (context_object, "window1");

   //Ocultar ventana anterior
   gtk_widget_hide(GTK_WIDGET(win));

   //Crear Ventana
   window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_container_set_border_width (GTK_CONTAINER (window2), 8);
	gtk_window_set_title (GTK_WINDOW (window2), "Tiempo de Ejecucion y Periodo");
	gtk_window_set_position (GTK_WINDOW (window2), GTK_WIN_POS_CENTER);   
	gtk_widget_realize (window2);
	//g_signal_connect (window2, "destroy", gtk_main_quit , NULL);

   // Create a box with buttons
	box = gtk_box_new (TRUE, 1);
   gtk_container_add (GTK_CONTAINER (window2), box);

   //Crear labels e input widgets
   gint N_tareas = grab_int_value( (gpointer)s_button,"");
   GtkWidget *label_t[N_tareas]; //Label Tiempo de Ejecucion
   GtkWidget *label_p[N_tareas]; //Label Periodo
   GtkWidget *entry_t[N_tareas]; //Input Tiempo de Ejecucion
   GtkWidget *entry_p[N_tareas]; //Input Periodo
   char label[100];
   for(int i = 0;i<N_tareas;i++){
      sprintf(label,"Tiempo de Ejecucion de Tarea %d: ",i+1);
      label_t[i] = gtk_label_new(label);
      sprintf(label,"Periodo de Tarea %d: ",i+1);
      label_p[i] = gtk_label_new(label);
      entry_t[i]= gtk_entry_new();
      entry_p[i]= gtk_entry_new();
      GtkWidget *hbox1 = gtk_box_new (FALSE, 1);
      GtkWidget *hbox2 = gtk_box_new (FALSE, 1);
      gtk_box_set_homogeneous (GTK_BOX (hbox1), TRUE);
      gtk_box_set_homogeneous (GTK_BOX (hbox2), TRUE);      
	   gtk_box_pack_start (GTK_BOX (box), hbox1, TRUE ,TRUE , 10);
	   gtk_box_pack_start (GTK_BOX (box), hbox2, TRUE ,TRUE , 10);      
	   gtk_box_pack_start (GTK_BOX (hbox1), label_t[i], TRUE ,TRUE , 10);
	   gtk_box_pack_start(GTK_BOX (hbox1), entry_t[i], TRUE ,TRUE , 10); 
	   gtk_box_pack_start (GTK_BOX (hbox2), label_p[i], TRUE ,TRUE , 10);
	   gtk_box_pack_start (GTK_BOX (hbox2), entry_p[i], TRUE ,TRUE , 10);
      sprintf(label,"entry_t%d",i+1);
      g_object_set_data (context_object, label,entry_t[i]);
      sprintf(label,"entry_p%d",i+1);
      g_object_set_data (context_object, label ,entry_p[i]);
   }
	b_next = gtk_button_new_with_label("Next");
	b_prev = gtk_button_new_with_label("Previous");

   g_object_set_data (context_object, "window2", window2);
	g_signal_connect (G_OBJECT (b_prev), "clicked", G_CALLBACK (prev_window_T),context_object );
   GtkWidget *label_correctitud = gtk_label_new(""); //Label que indica si las entradas son correctas
   g_object_set_data (context_object, "label_c",label_correctitud);
	g_signal_connect (G_OBJECT (b_next), "clicked", G_CALLBACK (test_e), context_object );
	gtk_box_pack_start (GTK_BOX (box), label_correctitud , TRUE, TRUE, 10);
   gtk_box_pack_start (GTK_BOX (box), b_next, TRUE, TRUE , 10);
	gtk_box_pack_start (GTK_BOX (box), b_prev,TRUE , TRUE, 10);


	gtk_widget_show_all (window2);
}

int main (int argc, char *argv[]){
	GtkWidget *s_button = NULL;
   GtkWidget *b_next = NULL;
	GtkWidget *win = NULL;
	GtkWidget *box = NULL;
	GtkWidget *label = NULL;
   
	/* Initialize GTK+ */
	g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
	gtk_init (&argc, &argv);
	g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
	
	/* Create the main window */
	win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width (GTK_CONTAINER (win), 8);
	gtk_window_set_title (GTK_WINDOW (win), "Numero de Tareas");
	gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
	gtk_widget_realize (win);
	g_signal_connect (win, "destroy", gtk_main_quit, NULL);
	
	// Create a vertical box with buttons
	box = gtk_box_new (TRUE, 6);
	gtk_container_add (GTK_CONTAINER (win), box);
	
   //Crear label
   label = gtk_label_new("Numero de tareas:");
   //Crear spin button
	s_button = create_integer_spin_button();
	//Crear boton next
	b_next = gtk_button_new_with_label("Next");
	
	//Meter widgets a la caja
	gtk_box_pack_start (GTK_BOX (box), label, TRUE, TRUE, 10);   
	gtk_box_pack_start (GTK_BOX (box), s_button, TRUE, TRUE, 10);
	gtk_box_pack_start (GTK_BOX (box), b_next, TRUE, TRUE, 10);

   //Senales
   g_object_set_data (G_OBJECT(b_next), "s_button", s_button);
   g_object_set_data (G_OBJECT(b_next), "window1", win );

   //function_par1 -> s_button = s_button;
   //function_par1 -> win = win;

	g_signal_connect (G_OBJECT (b_next), "clicked", G_CALLBACK (Ejec_Per), b_next );

	/* Enter the main loop */
	gtk_widget_show_all (win);
	gtk_main ();
	return 0;
}
