//
// Created by herbi on 26.05.2025.
//

#include "headargp.h"
#include <argp.h>
#include <stdlib.h>

const char *argp_program_version = "Xpath 0.1";
static char doc[]       = "Ein Demo Programm für XPATH";
static char args_doc[]  = "";

static struct argp_option options[] = {
    { "file", 'f', "FILE", 0, "HTML-Datei, z.B. -f index.html" },
    { "path", 'p', "PATH", 0, "Such-Pfad, z.B. -p div/div" " },
    { 0 }
};

/* Parser-Funktion */
static error_t parse_options(int key, char *arg, struct argp_state *state) {
    switch (key) {
        case 'f':
            arguments.file_path = arg;   // in struct arguments filepath = arg
            break;
        case 'p':
            arguments.path = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN; //error bei unknown input
    }
    return 0;
}

int parse_cmdline(int argc, char **argv) {
    struct argp parser = { options, parse_options, args_doc, doc };
    return argp_parse(&parser, argc, argv, 0, NULL, NULL);
}

/* Globale Variable mit Defaults */
struct Arguments arguments = {
    .file_path = DEFAULT_FILE,
    .path      = DEFAULT_PATH
};
