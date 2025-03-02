#include "storage.h"
#include <stdio.h>

// Fungsi untuk menyimpan kontak ke file CSV
void save_contacts_to_file(GList *contact_list, const gchar *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        g_print("Unable to open file for writing.\n");
        return;
    }

    // Menulis header CSV
    fprintf(file, "Name,Phone Number\n");

    // Menulis setiap kontak ke file CSV
    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;
        fprintf(file, "%s,%s\n", contact_get_name(contact), contact_get_phone_number(contact));
    }

    fclose(file);
    g_print("Contacts saved to %s\n", filename);
}

// Fungsi untuk memuat kontak dari file CSV
void load_contacts_from_file(GList **contact_list, const gchar *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        g_print("Unable to open file for reading.\n");
        return;
    }

    gchar name[100], phone[100];
    // Melewati header CSV
    fscanf(file, "%*[^\n]\n");

    // Membaca data kontak dan menambahkannya ke daftar
    while (fscanf(file, "%99[^,],%99[^\n]\n", name, phone) != EOF) {
        Contact *contact = contact_new(name, phone);
        *contact_list = g_list_append(*contact_list, contact);
    }

    fclose(file);
    g_print("Contacts loaded from %s\n", filename);
}