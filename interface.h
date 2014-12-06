#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "rotation.h"
#include "suppbruit.h"
#include <glib.h>

int main(int argc, char **argv);
void CloseWindow(GtkWidget *pWidget, gpointer pData);
void Binarize(GtkWidget *Widget, gpointer pData);
void Load(GtkWidget *pWidget, gpointer pdata);
void Rotation(GtkWidget *Widget, gpointer pdata);
void Removechildwidget(GtkWidget *Boxparent);
void CharaDetect(GtkWidget *pWidget, gpointer pData);
void GommageF(GtkWidget *pWidget, gpointer pData);
void RotBack(GtkWidget *pWidget, gpointer pData);
void NetF(GtkWidget *pWidget, gpointer pData);






GtkWidget* Resize(GtkWidget *Image, GtkWidget *window_parent, GdkPixbuf *pixbuf);

