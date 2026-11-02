/* fonctionnement similaire a une busybox */
#include <stdio.h>
#include <string.h>

#ifndef MAIN_NAME
#define MAIN_NAME "busybox"
#endif

/* Fonctions correspondant à chaque "applet" */
static int do_paul(int argc, char **argv)
{
    printf("Bonjour Paul\n");
    (void)argc; (void)argv;
    return 0;
}

static int do_bruno(int argc, char **argv)
{
    printf("Bonjour Bruno\n");
    (void)argc; (void)argv;
    return 0;
}

/* Extrait le nom de base de argv[0] (après le dernier '/') */
static const char *basename_of(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash ? slash + 1 : path;
}

/* Table des applets disponibles */
struct applet {
    const char *name;
    int (*fn)(int, char **);
};

static const struct applet applets[] = {
    { "paul",  do_paul  },
    { "bruno", do_bruno },
    { NULL,    NULL     }
};

int main(int argc, char **argv)
{
    const char *prog;
    int i;

    if (argc < 1 || argv[0] == NULL) {
        fprintf(stderr, "Erreur : argv[0] indisponible\n");
        return 1;
    }

    prog = basename_of(argv[0]);

    /* Mode 1 : appelé sous le nom du binaire principal
       → on lit la sous-commande dans argv[1]           */
    if (strcmp(prog, MAIN_NAME ) == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage : monprogramme <paul|bruno>\n");
            return 1;
        }
        prog = argv[1];
        argv++;   /* on décale : argv[0] devient la sous-commande */
        argc--;
    }

    /* Mode 2 (et suite du mode 1) : recherche de l'applet
       par le nom (lien ou sous-commande)                 */
    for (i = 0; applets[i].name != NULL; i++) {
        if (strcmp(prog, applets[i].name) == 0)
            return applets[i].fn(argc, argv);
    }

    fprintf(stderr, "%s : applet inconnue\n", prog);
    return 127;
}
