#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "rotation.h"
#include "suppbruit.h"
#include "binarisation.h"
#include <glib.h>
#include "detection.h"
#include "greytreat.h"

int main(int argc, char **argv);
void close_w(GtkWidget *pWidget, gpointer pData);
void Binarize(GtkWidget *Widget, gpointer pData);
void Load_Image(GtkWidget *pWidget, gpointer pdata);
void Rotation(GtkWidget *Widget, gpointer pdata);
void Removeson(GtkWidget *Boxparent);
void CharaDetect(GtkWidget *pWidget, gpointer pData);
void backrot(GtkWidget *pWidget, gpointer pData);
void NetF(GtkWidget *pWidget, gpointer pData);







GtkWidget* Resize(GtkWidget *Image, GtkWidget *window_parent, GdkPixbuf *pixbuf);

