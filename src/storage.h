#ifndef STORAGE_H
#define STORAGE_H

#include <glib.h>
#include "contact.h"

// Fungsi untuk menyimpan kontak ke file CSV
void save_contacts_to_file(GList *contact_list, const gchar *filename);

// Fungsi untuk memuat kontak dari file CSV
void load_contacts_from_file(GList **contact_list, const gchar *filename);

#endif
