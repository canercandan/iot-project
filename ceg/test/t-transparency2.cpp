#include <gtk/gtk.h>

static gboolean alpha_channel_support = FALSE;

static gboolean on_window_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
  cairo_t *cr;

  cr = gdk_cairo_create(widget->window); // create cairo context

  if(alpha_channel_support)
    // set source to RGB-Alpha
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.7);
  else
    // set source to RGB-Alpha
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // set color RGB

  cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE); // set drawing compositing operator
                                                 // SOURCE -> replace destination

  cairo_paint(cr); // paint source

  cairo_destroy(cr);

  return FALSE;
}

gint main(gint argc, gchar **argv)
{
  GtkWidget *window, *button, *vbox;
  GdkScreen *screen;
  GdkColormap *colormap;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(G_OBJECT(window), "delete-event", gtk_main_quit, NULL);
  g_signal_connect(G_OBJECT(window), "expose-event", G_CALLBACK(on_window_expose_event), NULL);

  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

  gtk_widget_set_app_paintable(window, TRUE); // allow application to paint on widget

  screen = gtk_widget_get_screen(window);

  colormap = gdk_screen_get_rgba_colormap(screen); // get colormap with alpha channel

  if(colormap != NULL)
    {
      alpha_channel_support = TRUE;
    }
  else
    {
      alpha_channel_support = FALSE;

      colormap = gdk_screen_get_rgb_colormap(screen);

      g_message("Screen supports no alpha channels\n");
    }

  gtk_widget_set_colormap(window, colormap);

  button = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(button), "Don't Press!");

  vbox = gtk_vbox_new(TRUE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(vbox));

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
