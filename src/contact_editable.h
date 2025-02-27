#ifndef CONTACT_EDITABLE_H
#define CONTACT_EDITABLE_H

#include <glib-object.h>

#define CONTACT_TYPE_EDITABLE (contact_editable_get_type())

G_DECLARE_INTERFACE(ContactEditable, contact_editable, CONTACT, EDITABLE, GObject)

struct _ContactEditableInterface {
    GTypeInterface parent_iface;

    void (*edit_name)(gpointer self, const gchar *new_name);
    void (*edit_phone_number)(gpointer self, const gchar *new_phone_number);
};

#endif