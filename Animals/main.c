#include "pre-animal.h"

int
main (int argc, char *argv[])
{
    g_type_init();

    PreAnimal *animal_1 = g_object_new (PRE_TYPE_ANIMAL, NULL);
    PreAnimal *animal_2 = g_object_new (PRE_TYPE_ANIMAL, NULL);

    pre_animal_set_age(animal_1, 5);
    pre_animal_set_age(animal_2, 10);

    g_print("\nAge %d", pre_animal_get_age(animal_1));
    g_print("\nAge %d", pre_animal_get_age(animal_2));

    return 0; 
}
