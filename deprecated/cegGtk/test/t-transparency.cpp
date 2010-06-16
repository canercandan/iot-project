#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <stdlib.h>

GtkWidget *window;
static gboolean alpha_channel_support = FALSE;

static gboolean
expose_window(GtkWidget *widget, GdkEventExpose *event, gpointer date)
{
  cairo_t *cr;

  cr = gdk_cairo_create(widget->window); /* create cairo context */

  if(alpha_channel_support){
    /* set source to RGB-Alpha */
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, .6);
    g_print("got alpha in expose");
  }else{
    /* set source to RGB-Alpha */
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); /* set color RGB */
  }

  /* set drawing compositing operator */
  cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
  /* SOURCE -> replace destination */

  cairo_paint(cr); /* paint source */

  cairo_destroy(cr);

  return FALSE;
}

int
setupwindow()
{
  GdkPixmap *background;
  GdkPixbuf *pixbuf;
  GdkPixbuf *scaled;
  GdkScreen *screen;
  GdkColormap *colormap;
  GError *error=NULL;
  GtkStyle *style;

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(window), "expose_event", G_CALLBACK(expose_window),NULL);
  gtk_window_set_title(GTK_WINDOW(window), "clock");
  gtk_window_stick(GTK_WINDOW(window));
  gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),TRUE);
  gtk_window_set_keep_above(GTK_WINDOW(window),TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 3);
  gtk_window_set_decorated(GTK_WINDOW(window),TRUE);
  gtk_window_set_default_size(GTK_WINDOW(window),100,100);
  gtk_widget_set_app_paintable(window,TRUE);

  /* Get the screen to get the colormap */
  screen=gtk_widget_get_screen(window);
  colormap = gdk_screen_get_rgba_colormap(screen);
  if(colormap != NULL){
    alpha_channel_support=TRUE;
  } else {
    alpha_channel_support=FALSE;
    colormap=gdk_screen_get_rgb_colormap(screen);
    g_print("Sorry, no alpha!\n");
  }
  /* Tell the window to use the colormap */
  gtk_widget_set_colormap(window,colormap);

  /* Get a pixbuf from the image file */
  pixbuf=gdk_pixbuf_new_from_file("clockface.png",&error);

  if(pixbuf==NULL){
    g_print("Failed to open background image: %s\n", error->message);
    g_error_free(error);
    error=NULL;
    return 0;
  }
  /* Make it the same size as the window */
  scaled=gdk_pixbuf_scale_simple(pixbuf,100,100, GDK_INTERP_BILINEAR);
  /* Render it using the colormap of the window */
  gdk_pixbuf_render_pixmap_and_mask_for_colormap(scaled,colormap,&background,NULL,0);
  /* Make a new style, stick the background in it, tell window to use it. */
  style = gtk_style_new();
  style->bg_pixmap[0] = background;
  gtk_widget_set_style(GTK_WIDGET(window),GTK_STYLE(style));

  /*gtk_window_set_opacity(GTK_WINDOW(window),0.3);*/
  gtk_window_move(GTK_WINDOW(window), 0, 0);
  gtk_widget_show_all(window);
  return 1;
}

int
main(int argc, char **argv)
{
  gtk_init(&argc,&argv);
  if(!setupwindow()){
    exit(EXIT_FAILURE);
  }
  gtk_main();
  exit(EXIT_SUCCESS);
}
