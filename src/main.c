#include <gtk/gtk.h>

static gboolean delete_event( GtkWidget* widget,
								GdkEvent* event,
								gpointer data)
{
	g_print("delete event occured\n");
	return FALSE;
}

static void destroy( GtkWidget* widget,
								gpointer data)
{
	gtk_main_quit();
}

static void clipboardevent(GtkClipboard *cp,
							GdkEvent *e,
							gpointer data)
{
	gchar* cc = gtk_clipboard_wait_for_text (cp);
	if (cc) {
		gtk_label_set_text(GTK_LABEL(data), cc);
		g_free (cc);
	}
}

int main( int   argc,
		  char *argv[] )
{
	GtkWidget *window = 0, *fixed = 0, *vbox = 0;
	GtkClipboard* clip = 0;
	GtkLabel* label = 0;
	GtkWidget* vte = 0;
	
	gtk_init (&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
	g_signal_connect (window, "delete-event", G_CALLBACK(delete_event), NULL);
	g_signal_connect (window, "destroy", G_CALLBACK(destroy), NULL);

	clip = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);

	gtk_container_set_border_width (GTK_CONTAINER(window), 10);

	vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_add (GTK_CONTAINER(window), vbox);
	gtk_widget_show (vbox);

	label = gtk_label_new ("hello world executable");
	g_signal_connect (clip, "owner-change", G_CALLBACK(clipboardevent), label);
	gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(label), FALSE, FALSE, 0);
	gtk_widget_show  (label);

	vte = vte_terminal_new ();
	gtk_box_pack_start(GTK_BOX(vbox), vte, FALSE, FALSE, 0);
	gtk_widget_show  (vte);

	gtk_widget_show  (GTK_WIDGET(window));
	
	gtk_main ();
	
	return 0;
}

