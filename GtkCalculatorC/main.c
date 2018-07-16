#include <stdlib.h>
#include <gtk/gtk.h>
#include "calculator.h"

static void on_clicked_clear(GtkWidget *widget, gpointer data)
{
    gtk_entry_set_text(GTK_ENTRY(data), "");
}

static void on_clicked_enter(GtkWidget* widget, gpointer data)
{
    const gchar* input = gtk_entry_get_text(GTK_ENTRY(data));
    double result = calculate(input);
    gchar* string = (gchar*)malloc(sizeof(gchar) * 255);
    g_snprintf(string, 255, "%g", result);
    gtk_entry_set_text(GTK_ENTRY(data), string);
}

static void place_char_in_entry(GtkEntry* entry, char c)
{
    GString* text = g_string_new(gtk_entry_get_text(entry));
    g_string_append_c(text, c);
    gtk_entry_set_text(entry, text->str);
    g_string_free(text, gtk_true());
}

static void on_clicked_num_or_op(GtkWidget *widget, gpointer data)
{
    const gchar* value = g_object_get_data(G_OBJECT(widget), "value");
    place_char_in_entry(GTK_ENTRY(data), value[0]);
}

static void activate(GtkApplication* app, gpointer user_data)
{
    GtkBuilder* builder = gtk_builder_new_from_file("layout.glade");
    GObject* window = gtk_builder_get_object(builder, "window");
    gtk_application_add_window(app, GTK_WINDOW(window));
    gtk_widget_show_all(GTK_WIDGET(window));

    GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry"));

    // assign values to each button
    // when the buttons are clicked, the corresponding values will be appended to the entry
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "zero")), "value", "0");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "one")), "value", "1");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "two")), "value", "2");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "three")), "value", "3");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "four")), "value", "4");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "five")), "value", "5");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "six")), "value", "6");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "seven")), "value", "7");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "eight")), "value", "8");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "nine")), "value", "9");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "add")), "value", "+");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "subtract")), "value", "-");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "multiply")), "value", "*");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "divide")), "value", "/");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "decimal")), "value", ".");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "lparen")), "value", "(");
    g_object_set_data(G_OBJECT(gtk_builder_get_object(builder, "rparen")), "value", ")");

    // bind 'clicked' signal handlers
    g_signal_connect(gtk_builder_get_object(builder, "clear"), "clicked", G_CALLBACK(on_clicked_clear), entry);

    g_signal_connect(gtk_builder_get_object(builder, "enter"), "clicked", G_CALLBACK(on_clicked_enter), entry);

    g_signal_connect(gtk_builder_get_object(builder, "zero"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "one"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "two"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "three"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "four"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "five"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "six"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "seven"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "eight"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "nine"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "add"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "subtract"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "multiply"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "divide"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "lparen"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "rparen"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
    g_signal_connect(gtk_builder_get_object(builder, "decimal"), "clicked", G_CALLBACK(on_clicked_num_or_op), entry);
}

int main(int argc, char* argv[])
{
    // create the application
    GtkApplication* app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return status;
}