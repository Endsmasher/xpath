//
// Created by herbi on 26.05.2025.
//

// headargp.h
#ifndef HEADARGP_H
#define HEADARGP_H

#define DEFAULT_FILE "test.txt"
#define DEFAULT_PATH "/"

struct Arguments {
    char *file_path;
    char *path;
};

extern struct Arguments arguments;

//ruft argp_parse intern auf und füllt arguments
int parse_cmdline(int argc, char **argv);

#endif // HEADARGP_H
