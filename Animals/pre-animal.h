/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __PRE_ANIMAL_H__
#define __PRE_ANIMAL_H__

#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

/*
 * Type macros.
 */
#define PRE_TYPE_ANIMAL                  (pre_animal_get_type ())
#define PRE_ANIMAL(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), PRE_TYPE_ANIMAL, PreAnimal))
#define PRE_IS_ANIMAL(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PRE_TYPE_ANIMAL))
#define PRE_ANIMAL_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), PRE_TYPE_ANIMAL, PreAnimalClass))
#define PRE_IS_ANIMAL_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), PRE_TYPE_ANIMAL))
#define PRE_ANIMAL_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), PRE_TYPE_ANIMAL, PreAnimalClass))

typedef struct _PreAnimal        PreAnimal;
typedef struct _PreAnimalClass   PreAnimalClass;
typedef struct _PreAnimalPrivate PreAnimalPrivate;

struct _PreAnimal
{
  GObject parent_instance;

  /*< private >*/
  PreAnimalPrivate *priv;

};

struct _PreAnimalClass
{
  GObjectClass parent_class;
};

void pre_animal_set_age (PreAnimal *self, gint age);
const int pre_animal_get_age (PreAnimal *self);

#endif

