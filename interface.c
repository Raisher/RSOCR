#include <gtk/gtk.h>
#include "detection.h"
  
static void cb_quit (GtkWidget * p_wid, gpointer p_data)
{
	gtk_main_quit ();
}

void Treatment(SDL_Surface *s,GdkPixbuf *pixbuf, GError *p_err)
{
	GdkPixbuf *pix = NULL;
	s=binarize(s);
	SDL_SaveBMP(s,"test_ocr.jpg");
	pixbuf = gdk_pixbuf_new_from_file("test_ocr.bmp",&p_err);
	
}

	  
int main (int argc, char ** argv)
{
	GtkBuilder  *p_builder   = NULL;
	GError      *p_err       = NULL;
	GtkWidget *imagebox = NULL;
	SDL_Surface *sdlimage = load_image("test_ocr.jpg");				 					  
	gtk_init (& argc, & argv);
	p_builder = gtk_builder_new ();
	GdkPixbuf *pixbuf = NULL;
	pixbuf = gdk_pixbuf_new_from_file("test_ocr.jpg",&p_err);
	pixbuf= gdk_pixbuf_scale_simple(pixbuf,600,800,GDK_INTERP_NEAREST);
	GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

														 
	if (p_builder != NULL)
	{
		gtk_builder_add_from_file (p_builder, "interface.xml", & p_err);								if (p_err == NULL)
		{
			GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
				p_builder, "RS OCR");
			GtkWidget *imagebox = (GtkWidget*) gtk_builder_get_object(p_builder,"box2"      );
			gtk_box_pack_start(GTK_BOX(imagebox),image,FALSE,FALSE,0);

																																										  g_signal_connect(
				gtk_builder_get_object (p_builder, "Rotate"),
				"clicked", G_CALLBACK (cb_quit),
				(gpointer) gtk_entry_get_text (
					GTK_ENTRY (gtk_builder_get_object (p_builder, "entry1"))
				)
	    );
																																											g_signal_connect (					
				gtk_builder_get_object (p_builder, "Process"),
			 "clicked", G_CALLBACK (Treatment), NULL);
			g_signal_connect(
				gtk_builder_get_object(p_builder,"Quit"),
				"clicked",G_CALLBACK(cb_quit),NULL);
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
