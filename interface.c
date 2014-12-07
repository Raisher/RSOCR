#include <stdlib.h>
#include "interface.h"

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
  GtkWidget *Entrybox;
  gchar *entry;
};


int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  //Window
  GtkWidget *pWindow, *pRotWindow;
  pRotWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), "RS OCR");
  gtk_window_set_title(GTK_WINDOW(pRotWindow), "Rotation");
  gtk_window_set_default_size(GTK_WINDOW(pWindow),1600,900 );
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_position(GTK_WINDOW(pRotWindow), GTK_WIN_POS_CENTER);
  gtk_widget_show(pWindow);
  g_signal_connect(G_OBJECT(pWindow), "destroy", 
  G_CALLBACK(CloseWindow), NULL);

  //Box and Buttons
  GtkWidget* pVBox1;
  GtkWidget* pVBox2;
  GtkWidget* pHBox1;
  GtkWidget* pHBox2;
  GtkWidget* pVBoxIm1;
  GtkWidget* pVBoxIm2;
  pVBox1 = gtk_vbox_new(FALSE,0);
  pVBox2 = gtk_vbox_new(FALSE,0);
  pHBox1 = gtk_hbox_new(FALSE,5);
  pHBox2 = gtk_hbox_new(FALSE,5);
  pVBoxIm1 = gtk_vbox_new(FALSE,0);
  pVBoxIm2 = gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pVBox1));
  gtk_box_pack_start(GTK_BOX(pVBox1), GTK_WIDGET(pHBox1),TRUE,TRUE, 1);
  gtk_box_pack_start(GTK_BOX(pVBox1), GTK_WIDGET(pVBox2),TRUE,TRUE, 1);
  gtk_box_pack_start(GTK_BOX(pVBox2), GTK_WIDGET(pHBox2),FALSE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(pHBox1), GTK_WIDGET(pVBoxIm1),FALSE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(pHBox1), GTK_WIDGET(pVBoxIm2),FALSE,TRUE,1);

  //Set blank first
  GtkWidget *pImage1 = NULL;
  GtkWidget *pImage2;
  GdkPixbuf *pixbuf1;
  GdkPixbuf *pixbuf2;
  GError *error = NULL;
  pixbuf1 = gdk_pixbuf_new_from_file("blank.jpg", &error);
  pixbuf2 = gdk_pixbuf_new_from_file("blank.jpg", &error);
	gdk_pixbuf_save(pixbuf1,"result.bmp","bmp",&error,NULL);
  //Button Load
  GtkWidget *pLoadBtn;
  open_picture picture;

  picture.pImage = pImage1;
  picture.path = NULL;
  picture.window_parent = pWindow;
  picture.box_parent = pVBoxIm1;
  picture.box_parent2 = pVBoxIm2;
  picture.pRotWin = pRotWindow;
  pLoadBtn = gtk_button_new_with_label("Load image");
  g_signal_connect(G_OBJECT(pLoadBtn),"clicked",G_CALLBACK(Load),&picture);

  //Button Binarize
  GtkWidget *pBinarizeBtn;
  pBinarizeBtn = gtk_button_new_with_label("Binarize");
  g_signal_connect(G_OBJECT(pBinarizeBtn),"clicked",G_CALLBACK(Binarize),
  &picture);

  //Button Charactere detection
  GtkWidget *pDetecBtn;
  pDetecBtn = gtk_button_new_with_label("Character Detection");
  g_signal_connect(G_OBJECT(pDetecBtn),"clicked",G_CALLBACK(CharaDetect),
  &picture);

  //Button Rotation
  GtkWidget *pRotateBtn;
  pRotateBtn = gtk_button_new_with_label("Rotate");

  //Widget posisitioning 
  gtk_box_pack_start(GTK_BOX(pHBox2), GTK_WIDGET(pLoadBtn), TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(pHBox2), GTK_WIDGET(pBinarizeBtn), TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(pHBox2), GTK_WIDGET(pRotateBtn), TRUE, TRUE, 5);
  gtk_box_pack_end(GTK_BOX(pHBox2), GTK_WIDGET(pDetecBtn), TRUE, TRUE, 5);
	pImage1 = Resize(pImage1,pWindow,pixbuf1);
	pImage2 = Resize(pImage2,pWindow,pixbuf2);
	gtk_box_pack_start(GTK_BOX(pVBoxIm1),pImage1,TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(pVBoxIm2),pImage2,TRUE,TRUE,5);
  //Rotate Entry Window
  GtkWidget *RotEntry;
  GtkWidget *RotVBox, *RotButton;
  RotButton = gtk_button_new_with_label("OK");
  picture.pRotOK = RotButton;
  g_signal_connect(G_OBJECT(pRotateBtn),"clicked",G_CALLBACK(RotBack),
  &picture);
  g_signal_connect(G_OBJECT(RotButton),"clicked",G_CALLBACK(Rotation),
  &picture);
  RotVBox = gtk_vbox_new(FALSE,0);
  RotEntry = gtk_entry_new();
  picture.Entrybox = RotEntry;
  gtk_container_add(GTK_CONTAINER(pRotWindow), GTK_WIDGET(RotVBox));
  gtk_box_pack_start(GTK_BOX(RotVBox), GTK_WIDGET(RotEntry), TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(RotVBox), GTK_WIDGET(RotButton), TRUE, TRUE, 5);


  gtk_widget_show_all(pWindow);	
  gtk_main();

  return EXIT_SUCCESS;
}

void CloseWindow(GtkWidget *pWidget,gpointer pData)
{
    if (pData != NULL && pWidget != NULL)
	{

	}
    gtk_main_quit();
}

void Binarize(GtkWidget *pWidget, gpointer pData)
{ 
  GtkWidget *Image = NULL, *Image2;
  GtkWidget *Boxparent,*Boxparent2, *parent_window = pWidget;
  GdkPixbuf *pixbuf, *pixbuf1;
  gchar *path;
  GError *error = NULL;

  open_picture *picture_struct = NULL;
  picture_struct = (open_picture*)pData;

  parent_window = picture_struct->window_parent;

  path = picture_struct->path;
  Boxparent2 = picture_struct->box_parent;
  Boxparent = picture_struct->box_parent2;
  if (path != NULL)
	{
		toGrayLevel(load_image("result.bmp"));
		otsu_th(load_image("result.bmp"),0);
		suppression(load_image("result.bmp"));
	}

  Removechildwidget(Boxparent);
  Removechildwidget(Boxparent2);

  pixbuf1 = gdk_pixbuf_new_from_file(path, &error);
  pixbuf = gdk_pixbuf_new_from_file("result.bmp", &error);
  Image = Resize(Image, parent_window, pixbuf);
  Image2 = Resize(Image, parent_window, pixbuf1);
  if (path != NULL)
  {
  gtk_box_pack_start(GTK_BOX(Boxparent2),Image2,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(Boxparent),Image,TRUE,TRUE,5);
  }
  gtk_widget_show_all(parent_window);

}

void CharaDetect(GtkWidget *pWidget, gpointer pData)
{
	GtkWidget *Image =NULL, *Image2;
	GtkWidget *Boxparent, *Boxparent2, *parent_window=pWidget;
	GdkPixbuf *pixbuf, *pixbuf1;
	gchar *path;
	GError *error = NULL;
	open_picture *picture_struct = NULL;
	picture_struct = (open_picture*)pData;
	parent_window = picture_struct->window_parent;
	path = picture_struct -> path;
	Boxparent=picture_struct->box_parent2;
	Boxparent2=picture_struct->box_parent;
	detect_block(load_image("result.bmp"));
	Removechildwidget(Boxparent);
	Removechildwidget(Boxparent2);
	pixbuf = gdk_pixbuf_new_from_file("result.bmp",&error);
	pixbuf1=gdk_pixbuf_new_from_file(path,&error);
	Image = Resize(Image,parent_window,pixbuf);
	Image2= Resize(Image,parent_window,pixbuf1);
	if(pixbuf!=NULL)
	{
		gtk_box_pack_start(GTK_BOX(Boxparent2),Image2,TRUE,TRUE,5);
		gtk_box_pack_start(GTK_BOX(Boxparent),Image,TRUE,TRUE,5);
	}
	gtk_widget_show_all(parent_window);
}

void Rotation(GtkWidget *pWidget, gpointer pData)
{
  
  GtkWidget *Image = NULL, *Image2;
  GtkWidget *Boxparent, *Boxparent2, *parent_window = pWidget;
  GdkPixbuf *pixbuf,*pixbuf1;
  gchar *path, *entry;
  GError *error = NULL;

  open_picture *picture_struct = NULL;
  picture_struct = (open_picture*)pData;
  gtk_widget_hide(picture_struct->pRotWin);
  GtkWidget *Entrybox = picture_struct->Entrybox;

  parent_window = picture_struct->window_parent;

  path = picture_struct->path;
  Boxparent = picture_struct->box_parent2;
  Boxparent2 = picture_struct->box_parent;
  entry = (gchar*)gtk_entry_get_text(GTK_ENTRY(Entrybox));
  if (entry != NULL)
	{
		otsu_th(load_image(path),1);
  	SDL_RotationCentralN(load_image("result.bmp"),strtof((char*)entry,NULL));
		//otsu_th(load_image("result.bmp"),0);
	}
  Removechildwidget(Boxparent);
  Removechildwidget(Boxparent2);

  pixbuf = gdk_pixbuf_new_from_file("result.bmp", &error);
  pixbuf1 = gdk_pixbuf_new_from_file(path, &error);
  Image = Resize(Image, parent_window, pixbuf);
  Image2 = Resize(Image, parent_window, pixbuf1);
  if (pixbuf != NULL)
  {
  gtk_box_pack_start(GTK_BOX(Boxparent2),Image2,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(Boxparent),Image,TRUE,TRUE,5);
  }
  gtk_widget_show_all(parent_window);
}


void RotBack(GtkWidget *pWidget, gpointer pData)
{
  open_picture *picture_struct = (open_picture*)pData;
  GtkWidget *rot_window = picture_struct->pRotWin; 
  GtkWidget *parent_window = pWidget;
  parent_window = picture_struct->window_parent;
  gtk_widget_show_all(rot_window);
  gtk_window_set_modal(GTK_WINDOW(rot_window), TRUE);
}

void Load(GtkWidget *pWidget, gpointer pData)
{

  GtkWidget *file_selection;
  GtkWidget *parent_window = pWidget;
  GtkWidget *Image = NULL, *Image2;
  GtkWidget *Boxparent;
  GtkWidget *Boxparent2;
  GdkPixbuf *pixbuf;
  GError *error = NULL;

  open_picture *picture_struct = NULL;

  picture_struct = (open_picture*)pData;
  parent_window = picture_struct->window_parent;
  Boxparent = picture_struct->box_parent;
  Boxparent2 = picture_struct->box_parent2;
  file_selection = 
        gtk_file_chooser_dialog_new("Select a file : ",
        GTK_WINDOW(parent_window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, GTK_RESPONSE_OK,
        NULL);
  gtk_window_set_modal(GTK_WINDOW(file_selection), TRUE);

  switch(gtk_dialog_run(GTK_DIALOG(file_selection)))
   {
    case GTK_RESPONSE_OK:
       {
        Removechildwidget(Boxparent);
        Removechildwidget(Boxparent2);
        picture_struct->path = 
				gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selection));
        pixbuf = gdk_pixbuf_new_from_file(picture_struct->path, &error);
        Image = Resize(Image, parent_window, pixbuf);
        Image2 = Resize(Image, parent_window, pixbuf);
				gdk_pixbuf_save(pixbuf,"result.bmp","bmp",&error,NULL);
        gtk_box_pack_start(GTK_BOX(Boxparent),Image,TRUE,TRUE,5);
        gtk_box_pack_start(GTK_BOX(Boxparent2),Image2,TRUE,TRUE,5);
        gtk_widget_show_all(parent_window);
       }
      	break;
    default:
      	break;
   }
  gtk_widget_destroy(file_selection);
}

GtkWidget *Resize(GtkWidget *Image, GtkWidget *window_parent,
GdkPixbuf *pixbuf)
{
  int x;
  int y;
  gtk_window_get_size(GTK_WINDOW(window_parent),&x,&y);
  GdkPixbuf *pixbuf_mini = NULL;
  pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf, (x/2)-20 , y-45 ,
  GDK_INTERP_NEAREST);
  Image = gtk_image_new_from_pixbuf(pixbuf_mini);
  return Image;
}

void Removechildwidget(GtkWidget *Boxparent)
{
  GList *children, *iter;
  children = gtk_container_get_children(GTK_CONTAINER(Boxparent));
  for(iter = children; iter != NULL; iter = g_list_next(iter))
   gtk_widget_destroy(GTK_WIDGET(iter->data));
  g_list_free(children);
}
