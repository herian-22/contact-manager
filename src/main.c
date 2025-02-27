#include <glib.h>
#include <stdio.h>
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

// Fungsi untuk mencari kontak berdasarkan nomor telepon
Contact* find_contact_by_phone(GList *contact_list, const gchar *phone_number) {
    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;
        if (g_strcmp0(contact_get_phone_number(contact), phone_number) == 0) {
            return contact;  // Kontak ditemukan
        }
    }
    return NULL;  // Kontak tidak ditemukan
}

void display_contacts(GList *contact_list) {
    if (g_list_length(contact_list) == 0) {
        g_print("No contacts available.\n");
        return;
    }

    g_print("Contacts List:\n");
    for (GList *l = contact_list; l != NULL; l = l->next) {
        Contact *contact = (Contact*)l->data;
        g_print("Name: %s, Phone: %s\n", contact_get_name(contact), contact_get_phone_number(contact));
    }
}

void delete_contact(GList **contact_list, const gchar *name) {
    GList *l = g_list_first(*contact_list);
    while (l != NULL) {
        Contact *contact = (Contact*)l->data;
        if (g_strcmp0(contact_get_name(contact), name) == 0) {
            *contact_list = g_list_remove(*contact_list, contact);
            g_object_unref(contact);
            g_print("Contact %s deleted successfully.\n", name);
            return;
        }
        l = l->next;
    }
    g_print("Contact %s not found.\n", name);
}

int main() {
    GList *contact_list = NULL;
    int choice;
    gchar name[100], phone[20];
    
    // Menu interaktif untuk pengguna
    while (1) {
        g_print("\nContact Manager:\n");
        g_print("1. Add Contact\n");
        g_print("2. Find Contact by Name\n");
        g_print("3. Find Contact by Phone Number\n");
        g_print("4. Delete Contact\n");
        g_print("5. Display All Contacts\n");
        g_print("6. Exit\n");
        g_print("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Add Contact
                g_print("Enter name: ");
                scanf("%s", name);
                g_print("Enter phone number: ");
                scanf("%s", phone);
                Contact *new_contact = contact_new(name, phone);
                contact_list = g_list_append(contact_list, new_contact);
                g_print("Contact added: %s, %s\n", name, phone);
                break;

            case 2:  // Find Contact by Name
                g_print("Enter name to search: ");
                scanf("%s", name);
                Contact *found_contact = find_contact_by_name(contact_list, name);
                if (found_contact != NULL) {
                    g_print("Found contact: %s, Phone: %s\n", contact_get_name(found_contact), contact_get_phone_number(found_contact));
                } else {
                    g_print("Contact %s not found.\n", name);
                }
                break;

            case 3:  // Find Contact by Phone Number
                g_print("Enter phone number to search: ");
                scanf("%s", phone);
                found_contact = find_contact_by_phone(contact_list, phone);
                if (found_contact != NULL) {
                    g_print("Found contact: %s, Phone: %s\n", contact_get_name(found_contact), contact_get_phone_number(found_contact));
                } else {
                    g_print("Contact with phone number %s not found.\n", phone);
                }
                break;

            case 4:  // Delete Contact
                g_print("Enter name to delete: ");
                scanf("%s", name);
                delete_contact(&contact_list, name);
                break;

            case 5:  // Display All Contacts
                display_contacts(contact_list);
                break;

            case 6:  // Exit
                g_list_free_full(contact_list, g_object_unref);
                g_print("Exiting program.\n");
                return 0;

            default:
                g_print("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}