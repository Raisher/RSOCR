#include <stdlib.h>
#include "interface.h"

typedef struct struct_picture struct_picture;
struct struct_picture
{
  GtkWidget *parent_window;
  gchar *path;
  GtkWidget *picture;
  GtkWidget *parent_box;
  GtkWidget *parent_box2;
  GtkWidget *Image;
  GtkWidget *RotWin;
  GtkWidget *OKbtn;
  GtkWidget *Entry;
  gchar *entry;
};


int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  //Window
  GtkWidget *pWindow, *RotWindow;
  RotWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow), "RS OCR");
  gtk_window_set_title(GTK_WINDOW(RotWindow), "Rotation");
  gtk_window_set_default_size(GTK_WINDOW(pWindow),1600,900 );
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_position(GTK_WINDOW(RotWindow), GTK_WIN_POS_CENTER);
  gtk_widget_show(pWindow);
  g_signal_connect(G_OBJECT(pWindow), "destroy",
  G_CALLBACK(close_w), NULL);

  //Box and Buttons
  GtkWidget* Box1;
  GtkWidget* Box2;
  GtkWidget* Hbox1;
  GtkWidget* Hbox2;
  GtkWidget* BoxIm1;
  GtkWidget* BoxIm2;
  Box1 = gtk_vbox_new(FALSE,0);
  Box2 = gtk_vbox_new(FALSE,0);
  Hbox1 = gtk_hbox_new(FALSE,5);
  Hbox2 = gtk_hbox_new(FALSE,5);
  BoxIm1 = gtk_vbox_new(FALSE,0);
  BoxIm2 = gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(Box1));
  gtk_box_pack_start(GTK_BOX(Box1),GTK_WIDGET(Hbox1),TRUE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(Box1),GTK_WIDGET(Box2),TRUE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(Box2),GTK_WIDGET(Hbox2),FALSE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(Hbox1),GTK_WIDGET(BoxIm1),FALSE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(Hbox1),GTK_WIDGET(BoxIm2),FALSE,TRUE,1);

  //Set blank first
  GtkWidget *Image1 = NULL;
  GtkWidget *Image2;
  GdkPixbuf *pixbuf1;
  GdkPixbuf *pixbuf2;
  GError *error = NULL;
  pixbuf1 = gdk_pixbuf_new_from_file("blank.jpg", &error);
  pixbuf2 = gdk_pixbuf_new_from_file("blank.jpg", &error);
	gdk_pixbuf_save(pixbuf1,"result.bmp","bmp",&error,NULL);
  //Button Load_Image
  GtkWidget *pLoad_ImageBtn;
  struct_picture picture;

  picture.Image = Image1;
  picture.path = NULL;
  picture.parent_window = pWindow;
  picture.parent_box = BoxIm1;
  picture.parent_box2 = BoxIm2;
  picture.RotWin = RotWindow;
  pLoad_ImageBtn = gtk_button_new_with_label("Load Image");
  g_signal_connect(G_OBJECT(pLoad_ImageBtn),"clicked",G_CALLBACK(Load_Image)	,&picture);

  //Button Binarize
  GtkWidget *pBinarizeBtn;
  pBinarizeBtn = gtk_button_new_with_label("Binarize");
  g_signal_connect(G_OBJECT(pBinarizeBtn),"clicked",G_CALLBACK(Binarize),
  &picture);

  //Button Charactere detection
  GtkWidget *pDetecBtn;
  pDetecBtn = gtk_button_new_with_label("Detection");
  g_signal_connect(G_OBJECT(pDetecBtn),"clicked",G_CALLBACK(CharaDetect),
  &picture);

  //Button Rotation
  GtkWidget *pRotateBtn;
  pRotateBtn = gtk_button_new_with_label("Rotate");

  //Widget posisitioning 
  gtk_box_pack_start(GTK_BOX(Hbox2), GTK_WIDGET(pLoad_ImageBtn), TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(Hbox2), GTK_WIDGET(pBinarizeBtn), TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(Hbox2), GTK_WIDGET(pRotateBtn), TRUE, TRUE, 5);
  gtk_box_pack_end(GTK_BOX(Hbox2), GTK_WIDGET(pDetecBtn), TRUE, TRUE, 5);
	Image1 = Resize(Image1,pWindow,pixbuf1);
	Image2 = Resize(Image2,pWindow,pixbuf2);
	gtk_box_pack_start(GTK_BOX(BoxIm1),Image1,TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(BoxIm2),Image2,TRUE,TRUE,5);
  //Rotate Entry Window
  GtkWidget *RotEntry;
  GtkWidget *RotVBox, *RotButton;
  RotButton = gtk_button_new_with_label("OK");
  picture.OKbtn = RotButton;
  g_signal_connect(G_OBJECT(pRotateBtn),"clicked",G_CALLBACK(backrot),
  &picture);
  g_signal_connect(G_OBJECT(RotButton),"clicked",G_CALLBACK(Rotation),
  &picture);
  RotVBox = gtk_vbox_new(FALSE,0);
  RotEntry = gtk_entry_new();
  picture.Entry = RotEntry;
  gtk_container_add(GTK_CONTAINER(RotWindow), GTK_WIDGET(RotVBox));
  gtk_box_pack_start(GTK_BOX(RotVBox), GTK_WIDGET(RotEntry), TRUE, TRUE, 5);
  gtk_box_pack_start(GTK_BOX(RotVBox), GTK_WIDGET(RotButton), TRUE, TRUE, 5);


  gtk_widget_show_all(pWindow);	
  gtk_main();

  return EXIT_SUCCESS;
}

void close_w(GtkWidget *pWidget,gpointer pData)
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

  struct_picture *picture_struct = NULL;
  picture_struct = (struct_picture*)pData;

  parent_window = picture_struct->parent_window;

  path = picture_struct->path;
  Boxparent2 = picture_struct->parent_box;
  Boxparent = picture_struct->parent_box2;
  if (path != NULL)
	{
		toGrayLevel(load_image("result.bmp"));
		otsu_th(load_image("result.bmp"),0);
		suppression(load_image("result.bmp"));
	}

  Removeson(Boxparent);
  Removeson(Boxparent2);
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
	struct_picture *picture_struct = NULL;
	picture_struct = (struct_picture*)pData;
	parent_window = picture_struct->parent_window;
	path = picture_struct -> path;
	Boxparent=picture_struct->parent_box2;
	Boxparent2=picture_struct->parent_box;
	Detection(load_image("result.bmp"));
	Removeson(Boxparent);
	Removeson(Boxparent2);
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
  struct_picture *picture_struct = NULL;
  picture_struct = (struct_picture*)pData;
  gtk_widget_hide(picture_struct->RotWin);
  GtkWidget *Entry = picture_struct->Entry;
  parent_window = picture_struct->parent_window;
  path = picture_struct->path;
  Boxparent = picture_struct->parent_box2;
  Boxparent2 = picture_struct->parent_box;
  entry = (gchar*)gtk_entry_get_text(GTK_ENTRY(Entry));
  if (entry != NULL)
	{
		otsu_th(load_image(path),1);
  	SDL_RotationCentralN(load_image("result.bmp"),strtof((char*)entry,NULL));
		//otsu_th(load_image("result.bmp"),0);
	}
  Removeson(Boxparent);
  Removeson(Boxparent2);
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


void backrot(GtkWidget *pWidget, gpointer pData)
{
  struct_picture *picture_struct = (struct_picture*)pData;
  GtkWidget *rot_window = picture_struct->RotWin; 
  GtkWidget *parent_window = pWidget;
  parent_window = picture_struct->parent_window;
  gtk_widget_show_all(rot_window);
  gtk_window_set_modal(GTK_WINDOW(rot_window), TRUE);
}

void Load_Image(GtkWidget *pWidget, gpointer pData)
{

  GtkWidget *select_file;
  GtkWidget *parent_window = pWidget;
  GtkWidget *Image = NULL, *Image2;
  GtkWidget *Boxparent;
  GtkWidget *Boxparent2;
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  struct_picture *picture_struct = NULL;
  picture_struct = (struct_picture*)pData;
  parent_window = picture_struct->parent_window;
  Boxparent = picture_struct->parent_box;
  Boxparent2 = picture_struct->parent_box2;
  select_file = 
        gtk_file_chooser_dialog_new("Select a file : ",
        GTK_WINDOW(parent_window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
        GTK_STOCK_OPEN, GTK_RESPONSE_OK,
        NULL);
  gtk_window_set_modal(GTK_WINDOW(select_file), TRUE);
  switch(gtk_dialog_run(GTK_DIALOG(select_file)))
   {
    case GTK_RESPONSE_OK:
       {
        Removeson(Boxparent);
        Removeson(Boxparent2);
        picture_struct->path = 
				gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(select_file));
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
  gtk_widget_destroy(select_file);
}
GtkWidget *Resize(GtkWidget *Image, GtkWidget *parent_window,
GdkPixbuf *pixbuf)
{
  int x;
  int y;
  gtk_window_get_size(GTK_WINDOW(parent_window),&x,&y);
  GdkPixbuf *pixbuf_mini = NULL;
  pixbuf_mini = gdk_pixbuf_scale_simple (pixbuf,(x/2)-20,y-45,
  GDK_INTERP_NEAREST);
  Image = gtk_image_new_from_pixbuf(pixbuf_mini);
  return Image;
}

void Removeson(GtkWidget *Boxparent)
{
  GList *son, *iterate;
  son = gtk_container_get_children(GTK_CONTAINER(Boxparent));
  for(iterate = son; iterate != NULL; iterate = g_list_next(iterate))
   gtk_widget_destroy(GTK_WIDGET(iterate->data));
  g_list_free(son);
}
