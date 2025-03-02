#include <gtk/gtk.h>
#include <glib.h>
#include "contact.h"
#include "storage.h"


GList *contact_list = NULL;
GtkWidget *listbox;
GtkWidget *name_entry;
GtkWidget *phone_entry;


void refresh_contact_list() {
    gtk_container_foreach(GTK_CONTAINER(listbox), (GtkCallback)gtk_widget_destroy, NULL);

    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact *)l->data;
        GtkWidget *row = gtk_label_new(g_strdup_printf("%s - %s", contact_get_name(contact), contact_get_phone_number(contact)));
        gtk_list_box_insert(GTK_LIST_BOX(listbox), row, -1);
    }

    gtk_widget_show_all(listbox);
}


static void on_add_contact(GtkWidget *widget, gpointer data) {
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    const gchar *phone_number = gtk_entry_get_text(GTK_ENTRY(phone_entry));

    if (g_strcmp0(name, "") != 0 && g_strcmp0(phone_number, "") != 0) {
        Contact *new_contact = contact_new(name, phone_number);
        contact_list = g_list_append(contact_list, new_contact);
        refresh_contact_list();

        
        gtk_entry_set_text(GTK_ENTRY(name_entry), "");
        gtk_entry_set_text(GTK_ENTRY(phone_entry), "");
    }
}

static void on_save_contacts(GtkWidget *widget, gpointer data) {
    save_contacts_to_file(contact_list, "contacts.csv");
    g_print("Contacts saved to file.\n");
}


static void on_delete_contact(GtkWidget *widget, gpointer data) {
    GtkListBoxRow *selected_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox));
    if (selected_row) {
        GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_row));
        const gchar *contact_info = gtk_label_get_text(GTK_LABEL(label));

        gchar **split = g_strsplit(contact_info, " - ", 2);
        const gchar *name = split[0];

        
        GList *l = contact_list;
        while (l != NULL) {
            Contact *contact = (Contact *)l->data;
            if (g_strcmp0(contact_get_name(contact), name) == 0) {
                contact_list = g_list_remove(contact_list, contact);
                g_object_unref(contact);
                break;
            }
            l = l->next;
        }

        refresh_contact_list();
        g_strfreev(split);
    }
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);


    load_contacts_from_file(&contact_list, "contacts.csv");


    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Contact Manager");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Enter Name");
    phone_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Enter Phone Number");

  
    GtkWidget *add_button = gtk_button_new_with_label("Add Contact");
    g_signal_connect(add_button, "clicked", G_CALLBACK(on_add_contact), NULL);


    listbox = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(box), name_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), phone_entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), add_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), listbox, TRUE, TRUE, 0);


    GtkWidget *save_button = gtk_button_new_with_label("Save Contacts");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_contacts), NULL);
    gtk_box_pack_start(GTK_BOX(box), save_button, FALSE, FALSE, 0);


    GtkWidget *delete_button = gtk_button_new_with_label("Delete Selected");
    g_signal_connect(delete_button, "clicked", G_CALLBACK(on_delete_contact), NULL);
    gtk_box_pack_start(GTK_BOX(box), delete_button, FALSE, FALSE, 0);


    refresh_contact_list();

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}