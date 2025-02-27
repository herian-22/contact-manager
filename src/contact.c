#include "contact.h"

struct _Contact {
    GObject parent_instance;
    gchar *name;
    gchar *phone_number;
};

G_DEFINE_TYPE(Contact, contact, G_TYPE_OBJECT)

static void contact_dispose(GObject *object) {
    Contact *self = (Contact*)object;  // Casting langsung
    g_clear_pointer(&self->name, g_free);
    g_clear_pointer(&self->phone_number, g_free);
    G_OBJECT_CLASS(contact_parent_class)->dispose(object);
}

static void contact_class_init(ContactClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = contact_dispose;
}

static void contact_init(Contact *self) {
    // Inisialisasi instance
}

Contact* contact_new(const gchar *name, const gchar *phone_number) {
    Contact *self = g_object_new(TYPE_CONTACT, NULL);
    self->name = g_strdup(name);
    self->phone_number = g_strdup(phone_number);
    return self;
}

const gchar* contact_get_name(Contact *self) {
    return self->name;
}

const gchar* contact_get_phone_number(Contact *self) {
    return self->phone_number;
}

void contact_set_name(Contact *self, const gchar *name) {
    g_free(self->name);
    self->name = g_strdup(name);
}

void contact_set_phone_number(Contact *self, const gchar *phone_number) {
    g_free(self->phone_number);
    self->phone_number = g_strdup(phone_number);
}