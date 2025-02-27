#include "storage.h"
#include <stdio.h>

// Fungsi untuk menyimpan kontak ke file CSV
void save_contacts_to_file(GList *contact_list, const gchar *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        g_print("Unable to open file for writing.\n");
        return;
    }

    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;
        fprintf(file, "%s,%s\n", contact_get_name(contact), contact_get_phone_number(contact));
    }

    fclose(file);
}

// Fungsi untuk memuat kontak dari file CSV
void load_contacts_from_file(GList **contact_list, const gchar *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        g_print("Unable to open file for reading.\n");
        return;
    }

    gchar name[100], phone[100];
    while (fscanf(file, "%99[^,],%99[^\n]\n", name, phone) != EOF) {
        Contact *contact = contact_new(name, phone);
        *contact_list = g_list_append(*contact_list, contact);
    }

    fclose(file);
}