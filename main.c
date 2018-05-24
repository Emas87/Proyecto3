#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

void Algoritmos(GtkWidget *widget, gpointer user_data){

}
void sure(GtkWidget *widget,gpointer context_object)
{
   GtkWidget *dialog = NULL;
   GtkWidget *curr = g_object_get_data (context_object, "curr");
   //dialog = gtk_message_dialog_new (GTK_WINDOW (curr), GTK_DIALOG_MODAL , GTK_MESSAGE_INFO , GTK_BUTTONS_YES_NO, "Esta seguro que quiere salir?");
   dialog = gtk_message_dialog_new (GTK_WINDOW (curr), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
   gtk_window_set_title(GTK_WINDOW(dialog), "Salir?");
   gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
   if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_YES){
      gtk_main_quit();
   }
   gtk_widget_destroy (dialog);


}
void prev_window(GtkWidget *widget, gpointer context_object ){
   GtkWidget *prev = g_object_get_data (context_object, "prev");
   GtkWidget *curr = g_object_get_data (context_object, "curr");
	gtk_widget_show(prev);
   gtk_widget_destroy(curr);
}
gint grab_int_value (GtkSpinButton *button, gpointer user_data){
   return gtk_spin_button_get_value_as_int (button);
}

GtkWidget* create_integer_spin_button (void){
   GtkWidget *window, *button;
   GtkAdjustment *adjustment;
   adjustment = gtk_adjustment_new (1, 1, 6, 1, 1, 0);
   button = gtk_spin_button_new (adjustment, 1, 0);
   return button;
}

static void Ejec_Per (GtkWidget *wid,gpointer context_object){
   GtkWidget *window2 = NULL;
  	GtkWidget *box = NULL;
   GtkWidget *b_next = NULL;
   GtkWidget *b_prev = NULL;
   GtkWidget *s_button = g_object_get_data (context_object, "s_button");
   GtkWidget *win = g_object_get_data (context_object, "top_win");

   //Ocultar ventana anterior
   gtk_widget_hide(GTK_WIDGET(win));

   //Crear Ventana
   window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_container_set_border_width (GTK_CONTAINER (window2), 8);
	gtk_window_set_title (GTK_WINDOW (window2), "Tiempo de Ejecucion y Periodo");
	gtk_window_set_position (GTK_WINDOW (window2), GTK_WIN_POS_CENTER);   
	gtk_widget_realize (window2);
   g_object_set_data (context_object, "prev", win);
   g_object_set_data (context_object, "curr", window2 );
	g_signal_connect (window2, "destroy",G_CALLBACK (sure) , context_object);

   // Create a box with buttons
	box = gtk_box_new (TRUE, 6);
   gtk_container_add (GTK_CONTAINER (window2), box);

   //Crear labels e input widgets
   gint N_tareas = grab_int_value( (gpointer)s_button,"");
   GtkWidget *label_t[N_tareas]; //Label Tiempo de Ejecucion
   GtkWidget *label_p[N_tareas]; //Label Periodo

   for(int i = 0;i<N_tareas;i++){
      label_t[i] = gtk_label_new("Tiempo de Ejecucion: ");
      label_p[i] = gtk_label_new("Periodo: ");
	   gtk_box_pack_start (GTK_BOX (box), label_t[i], TRUE, TRUE, 10); 
	   gtk_box_pack_start (GTK_BOX (box), label_p[i], TRUE, TRUE, 10); 
   }
	b_next = gtk_button_new_with_label("Next");
	b_prev = gtk_button_new_with_label("Previous");

	gtk_box_pack_start (GTK_BOX (box), b_next, TRUE, TRUE, 10);
	gtk_box_pack_start (GTK_BOX (box), b_prev, TRUE, FALSE, 10);
	g_signal_connect (G_OBJECT (b_next), "clicked", G_CALLBACK (Algoritmos), context_object );
	g_signal_connect (G_OBJECT (b_prev), "clicked", G_CALLBACK (prev_window),context_object );

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
   g_object_set_data (G_OBJECT(b_next), "top_win", win );

   //function_par1 -> s_button = s_button;
   //function_par1 -> win = win;

	g_signal_connect (G_OBJECT (b_next), "clicked", G_CALLBACK (Ejec_Per), b_next );

	/* Enter the main loop */
	gtk_widget_show_all (win);
	gtk_main ();
	return 0;
}
