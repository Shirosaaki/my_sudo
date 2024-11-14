/*
** EPITECH PROJECT, 2024
** my
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
    #include <security/pam_appl.h>
    #include <security/pam_misc.h>
    #include <sys/wait.h>
    #include <sys/capability.h>
    #include "../lib/my/my.h"

int my_strncmp(char *s1, char *s2, int n);
char *my_strcat(char *dest, char *src);
char **my_str_to_word_array(char *str, char separator);
void free_tab(char **tab);

#endif /* !MY_H_ */
