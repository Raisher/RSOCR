#include "interface.h"
#include "rotation.h" 
#include <glib.h> 

typedef struct open_picture open_picture;
struct open_picture
{
	GtkWidget *window_parent;
	gchar *path;
	GtkWidget *picture;
	GtkWidget *box_parent;
	GtkWidget *box_parent2;
	GtkWidget *pImage;
	GtkWidget *pRotWin;
	GtkWidget *pRotOK;
	GtkWidget *Gommage;
	GtkWidget *Net;
	GtkWidget *Entrybox;
	gchar *entry;
};

static void cb_quit (GtkWidget * p_wid, gpointer pdata)
{
	gtk_main_quit ();

}



void Binarize(GtkWidget *Widget, gpointer pdata)
{
		
}

void Load(GtkWidget *pWidget, gpointer pdata)
{
	GtkWidget *file_selection;
	GtkWidget *parent_window = pWidget;
	GtkWidget *Image =NULL, *Image2;
	GtkWidget *Boxparent;
	GtkWidget *Boxparent2;
	GdkPixbuf *pixbuf;
	GError *error = NULL;

	open_picture *picture_struct = NULL;
	picture_struct = (open_picture*)pdata;
	parent_window = picture_struct->window_parent;
	Boxparent = picture_struct ->box_parent;
	Boxparent2 = picture_struct->box_parent2;
	file_selection = 
	gtk_file_chooser_dialog_new("Select the file you want to open : ", 
	GTK_WINDOW(parent_window), 
	GTK_FILE_CHOOSER_ACTION_OPEN, 
	GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, 
	GTK_STOCK_OPEN,GTK_RESPONSE_OK,NULL);

		gtk_window_set_modal(GTK_WINDOW(file_selection),TRUE);
		switch(gtk_dialog_run(GTK_DIALOG(file_selection)))
		{
			case GTK_RESPONSE_OK:
			{
				Removechildwidget(Boxparent);
				Removechildwidget(Boxparent2);
				//picture_struct->path = gtk_file_chooser_get_filename(
				//GTK_FILE_CHOOSER(file_selection));
				//pixbuf = gdk_pixbuf_new_from_file(picture_struct->path,&error);
				//Image = Resize(Image,parent_window,pixbuf);
				//Image2=Resize(Image2,parent_window,pixbuf);
				//gtk_box_pack_start(GTK_BOX(Boxparent),Image,TRUE,TRUE,5);
				//gtk_box_pack_start(GTK_BOX(Boxparent2),Image2,TRUE,TRUE,5);
				//gtk_widget_show_all(parent_window);
			}
				break;
			default :
				break;
		}
		gtk_widget_destroy(file_selection);
}

void Rotate(GtkWidget *Widget, gpointer pdata)
{
	GtkWidget *Image =NULL, *Image2;
	GtkWidget *Boxparent, *Boxparent2, *parent_window = Widget;
	GdkPixbuf *pixbuf,*pixbuf1;
	gchar *path, *entry;
	GError *error = NULL;

	open_picture *picture_struct = NULL;
	picture_struct = (open_picture*)pdata;
	GtkWidget *Entrybox = picture_struct->Entrybox;

	parent_window = picture_struct->window_parent;
	path = picture_struct->path;
	Boxparent = picture_struct->box_parent2;
	Boxparent2 = picture_struct->box_parent;
	entry = (gchar*)gtk_entry_get_text(GTK_ENTRY(Entrybox));
	if(entry!=NULL)
	{
		SDl_RotationCentralN(load_image(path),strtof((char*)entry,NULL));
	}

	Removechildwidget(Boxparent);
	Removechildwidget(Boxparent2);

	pixbuf = gdk_pixbuf_new_from_file("result.bmp",&error);
	pixbuf1 = gdk_pixbuf_new_from_file(path,&error);
	Image = Resize(Image,parent_window,pixbuf);
	Image2=Resize(Image2,parent_window,pixbuf1);
	if (pixbuf!=NULL)
	{
		gtk_box_pack_start(GTK_BOX(Boxparent2),Image2,TRUE,TRUE,5);
		gtk_box_pack_start(GTK_BOX(Boxparent),Image,TRUE,TRUE,5);
	}
	gtk_widget_show_all(parent_window);	
}


	  
void main(int argc, char **argv)
{
	GtkBuilder  *p_builder   = NULL;
	GError      *p_err       = NULL;
	struct open_picture *picture = malloc(sizeof(struct open_picture));			 					  
	gtk_init (& argc, & argv);
	p_builder = gtk_builder_new ();
	GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file("newtest.jpg",&p_err);   
	GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file("blank.jpg",&p_err);
	picture->pImage = NULL;
	picture->path = NULL;
	GtkWidget *image1 = NULL, *image2 = NULL;

														 
	if (p_builder != NULL)
	{
		gtk_builder_add_from_file (p_builder, "interface.xml", & p_err);								if (p_err == NULL)
		{
			GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
				p_builder, "RS OCR");
			picture->window_parent = p_win;
			GtkWidget *image1box = (GtkWidget*) gtk_builder_get_object(p_builder,"Image1");
			picture->box_parent = image1box;
			GtkWidget *image2box = (GtkWidget*) gtk_builder_get_object(p_builder,"Image2");
			picture->box_parent2 = image2box;
			image1 = gtk_image_new_from_file("newtest.jpg");
			image2 = gtk_image_new_from_file("blank.jpg");
			image1=Resize(image1,p_win,pixbuf1);
			image2=Resize(image2,p_win,pixbuf2);
			gtk_box_pack_start(GTK_BOX(image1box),image1,TRUE,TRUE,5);
			gtk_box_pack_start(GTK_BOX(image2box),image2,TRUE,TRUE,5);

																																										  g_signal_connect(
				gtk_builder_get_object (p_builder, "Rotate"),
				"clicked", G_CALLBACK (Rotate),&picture);
					g_signal_connect (					
				gtk_builder_get_object (p_builder, "Binarize"),
			 "clicked", G_CALLBACK (Binarize), &picture);
			g_signal_connect(
				gtk_builder_get_object(p_builder,"Quit"),
				"clicked",G_CALLBACK(cb_quit),NULL);
			g_signal_connect(
				gtk_builder_get_object(p_builder,"Load"),
				"clicked",G_CALLBACK(Load),&picture);

			gtk_widget_show_all (p_win);
			gtk_main ();

		}
		else
		{
			g_error ("%s", p_err->message);
			g_error_free (p_err);
		}
	}
}

void Removechildwidget(GtkWidget *Boxparent)
{
	GList *children, *iter;
	children = gtk_container_get_children(GTK_CONTAINER(Boxparent));
	for (iter = children; iter != NULL; children = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);
}

GtkWidget* Resize(GtkWidget *Image, GtkWidget *window_parent, GdkPixbuf *pixbuf){
	int x;
	int y;
	gtk_window_get_size(GTK_WINDOW(window_parent),&x,&y);
	GdkPixbuf *pixbuf_mini = NULL;
	pixbuf_mini = gdk_pixbuf_scale_simple(pixbuf,500,600,GDK_INTERP_NEAREST);
	Image = gtk_image_new_from_pixbuf(pixbuf_mini);
	return Image;
}
