// src/contact.h
#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define TYPE_CONTACT (contact_get_type())
G_DECLARE_FINAL_TYPE(Contact, contact, CONTACT, OBJECT, GObject)

Contact* contact_new(const gchar *name, const gchar *phone_number);
const gchar* contact_get_name(Contact *self);
const gchar* contact_get_phone_number(Contact *self);
void contact_set_name(Contact *self, const gchar *name);
void contact_set_phone_number(Contact *self, const gchar *phone_number);

G_END_DECLS
