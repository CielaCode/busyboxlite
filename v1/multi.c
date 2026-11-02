#include <stdio.h>
#include <string.h>

/* Extrait le nom de base de argv[0] (la partie après le dernier '/') */
static const char *basename_of(const char *path)
{
    const char *slash = strrchr(path, '/');
    return slash ? slash + 1 : path;
}

int main(int argc, char **argv)
{
    const char *prog;

    if (argc < 1 || argv[0] == NULL) {
        fprintf(stderr, "Erreur : argv[0] indisponible\n");
        return 1;
    }

    prog = basename_of(argv[0]);

    if (strcmp(prog, "paul") == 0) {
        printf("Bonjour Paul\n");
    } else if (strcmp(prog, "bruno") == 0) {
        printf("Bonjour Bruno\n");
    } else {
        printf("Bonjour inconnu (appelé sous le nom : %s)\n", prog);
    }

    return 0;
}
