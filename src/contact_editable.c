#include "contact_editable.h"

G_DEFINE_INTERFACE(ContactEditable, contact_editable, G_TYPE_OBJECT)

static void contact_editable_default_init(ContactEditableInterface *iface) {
    iface->edit_name = NULL;
    iface->edit_phone_number = NULL;
}

// Implementasi fungsi edit_name dan edit_phone_number akan dilakukan di kelas turunannya.
