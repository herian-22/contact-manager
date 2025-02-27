#include <glib.h>
#include "contact.h"

void print_contact(Contact *contact) {
    g_print("Name: %s, Phone Number: %s\n",
            contact_get_name(contact),
            contact_get_phone_number(contact));
}

int main() {
    GList *contact_list = NULL;

    // Menambahkan kontak
    Contact *alice = contact_new("Alice", "123-456-7890");
    Contact *bob = contact_new("Bob", "098-765-4321");
    contact_list = g_list_append(contact_list, alice);
    contact_list = g_list_append(contact_list, bob);

    // Menampilkan semua kontak
    g_print("Contact List:\n");
    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;  // Casting langsung
        print_contact(contact);
    }

    // Menghapus kontak
    contact_list = g_list_remove(contact_list, alice);
    g_object_unref(alice);

    // Menampilkan kontak setelah penghapusan
    g_print("\nAfter removing Alice:\n");
    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;  // Casting langsung
        print_contact(contact);
    }

    // Membersihkan sisa daftar kontak
    g_list_free_full(contact_list, g_object_unref);

    return 0;
}
