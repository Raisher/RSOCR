#include <gtk/gtk.h>
#include <stdlib.h>

static void cb_ok (GtkWidget * p_wid, gpointer p_data)
{
  GtkWidget   * p_dialog  = NULL;
  const char  * p_text    = p_data;
	
	if (p_text != NULL)
	{
		p_dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"%s",p_text);
													 
													  
		gtk_dialog_run (GTK_DIALOG (p_dialog));
		gtk_widget_destroy (p_dialog);
	}
}
 
  
static void cb_quit (GtkWidget * p_wid, gpointer p_data)
{
	gtk_main_quit ();
}
	 
	  
int main (int argc, char ** argv)
{
	GtkBuilder  *p_builder   = NULL;
	GError      *p_err       = NULL;
						 					  
	gtk_init (& argc, & argv);
	p_builder = gtk_builder_new ();
														 
	if (p_builder != NULL)
	{
		gtk_builder_add_from_file (p_builder, "interface.xml", & p_err);								if (p_err == NULL)
		{
			GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
				p_builder, "RS OCR");
																																										  g_signal_connect(
				gtk_builder_get_object (p_builder, "Rotate"),
				"clicked", G_CALLBACK (cb_ok),
				(gpointer) gtk_entry_get_text (
					GTK_ENTRY (gtk_builder_get_object (p_builder, "entry1"))
				)
	    );
																																											g_signal_connect (
				gtk_builder_get_object (p_builder, "Binarize"),
			 "clicked", G_CALLBACK (cb_quit), NULL
			);
																																											gtk_widget_show_all (p_win);
			gtk_main ();
		}
		else
		{
			g_error ("%s", p_err->message);
			g_error_free (p_err);
		}
	}
	return EXIT_SUCCESS;
}
