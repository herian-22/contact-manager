#include <glib.h>
#include "contact.h"

// Fungsi untuk mencari kontak berdasarkan nama
Contact* find_contact_by_name(GList *contact_list, const gchar *name) {
    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;
        if (g_strcmp0(contact_get_name(contact), name) == 0) {
            return contact;  // Kontak ditemukan
        }
    }
    return NULL;  // Kontak tidak ditemukan
}

int main() {
    GList *contact_list = NULL;

    // Menambahkan kontak
    Contact *alice = contact_new("Alice", "123-456-7890");
    Contact *bob = contact_new("Bob", "098-765-4321");
    contact_list = g_list_append(contact_list, alice);
    contact_list = g_list_append(contact_list, bob);

    // Mencari kontak berdasarkan nama
    const gchar *search_name = "Alice";
    Contact *found_contact = find_contact_by_name(contact_list, search_name);
    if (found_contact != NULL) {
        g_print("Found contact: %s, Phone: %s\n", contact_get_name(found_contact), contact_get_phone_number(found_contact));
    } else {
        g_print("Contact %s not found.\n", search_name);
    }

    // Membersihkan sisa daftar kontak
    g_list_free_full(contact_list, g_object_unref);
    return 0;
}