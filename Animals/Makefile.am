include $(INTROSPECTION_MAKEFILE)

pkglib_LTLIBRARIES = libanimal-1.0.la

libanimal_1_0_la_SOURCES = \
    ./pre-animal.h \
    ./pre-animal.c

libanimal_1_0_la_CFLAGS = \
    `pkg-config --cflags dbus-glib-1` \
    `pkg-config --cflags dbus-1` \
    `pkg-config --cflags glib-2.0`

libanimal_1_0_la_LDFLAGS = \
    -avoid-version


INTROSPECTION_GIRS = Animal-1.0.gir

Animal-1.0.gir: libanimal-1.0.la Makefile
Animal_1_0_gir_NAMESPACE = PreAnimal
Animal_1_0_gir_VERSION = 1.0
Animal_1_0_gir_LIBS = libanimal-1.0.la
Animal_1_0_gir_SCANNERFLAGS = --warn-all --symbol-prefix=pre_animal --identifier-prefix=PreAnimal
Animal_1_0_gir_INCLUDES = \
    GObject-2.0 \
    Gio-2.0
Animal_1_0_gir_CFLAGS = \
    `pkg-config --cflags dbus-glib-1` \
    `pkg-config --cflags dbus-1` \
    `pkg-config --cflags glib-2.0`
Animal_1_0_gir_FILES = \
    ./pre-animal.h \
    ./pre-animal.c

girdir = $(pkgdatadir)/gir-1.0
typelibdir = $(pkglibdir)/girepository-1.0
gir_DATA = $(INTROSPECTION_GIRS)
typelib_DATA = $(gir_DATA:.gir=.typelib)
CLEANFILES = $(gir_DATA) $(typelib_DATA)
