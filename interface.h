#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static void cb_ok(GtkWidget *p_wid, gpointer p_data);
static void cb_quit(GtkWidget *p_wid, gpointer p_data);
void init (int argc, char **argv);
void Binarize(GtkWidget *p_wid, gpointer pdata);
void Binarize(GtkWidget *Widget, gpointer pdata);
void Load(GtkWidget *pWidget, gpointer pdata);
void Rotate(GtkWidget *Widget, gpointer pdata);
void Removechildwidget(GtkWidget *Boxparent);
GtkWidget* Resize(GtkWidget *Image, GtkWidget *window_parent, GdkPixbuf *pixbuf);

