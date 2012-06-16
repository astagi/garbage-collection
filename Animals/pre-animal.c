#include "pre-animal.h"

#define PRE_ANIMAL_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), PRE_TYPE_ANIMAL, PreAnimalPrivate))

G_DEFINE_TYPE (PreAnimal, pre_animal, G_TYPE_OBJECT);

struct _PreAnimalPrivate
{
    int age;
};

static void
pre_animal_init (PreAnimal *self)
{

    g_print("\npre_animal_init");

    self->priv = PRE_ANIMAL_GET_PRIVATE(self);
    self->priv->age = 0;
}

static void
pre_animal_class_init (PreAnimalClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
    g_print("\nprevoid_animal_class_init");
    g_type_class_add_private (klass, sizeof (PreAnimalPrivate));
}

/**
 * pre_animal_set_age:
 * @self: a #PreAnimal
 * @age: the new age of our animal
 *
 * Set the age of our animal.
 */
void
pre_animal_set_age (PreAnimal *self, gint age)
{
    g_return_if_fail (PRE_IS_ANIMAL (self));
    self->priv->age = age;
}

/**
 * pre_animal_get_age:
 * @self: a #PreAnimal
 *
 * Return value: the age of the animal
 */
const int pre_animal_get_age (PreAnimal *self)
{
    g_return_if_fail (PRE_IS_ANIMAL (self));
    return self->priv->age;
}
