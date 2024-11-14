/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/
#include "include/my.h"

int authenticate(void)
{
    pam_handle_t *pamh = NULL;
    int retval;
    struct passwd *pw;
    struct pam_conv pam_conversation = { misc_conv, NULL };
    char *user;

    pw = getpwuid(geteuid());
    if (!pw)
        return 0;
    user = pw->pw_name;
    if (!user)
        return 0;
    retval = pam_start("sudo", user, &pam_conversation, &pamh);
    retval = pam_authenticate(pamh, 0);
    retval = pam_acct_mgmt(pamh, 0);
    pam_end(pamh, PAM_SUCCESS);
    return 1;
}

int execute(char **tab, char **env, int r)
{
    char **paths = NULL;
    char **tmp = NULL;
    char *cmd = NULL;

    execve(tab[0], tab, env);
    for (int i = 0; env[i] != NULL; i++) {
        tmp = my_str_to_word_array(env[i], '=');
        if (my_strncmp(tmp[0], "PATH", 4) == 0) {
            paths = my_str_to_word_array(tmp[1], ':');
            break;
        }
        free_tab(tmp);
    }
    for (int i = 0; paths[i] != NULL; i++) {
        cmd = my_strcat(paths[i], "/");
        cmd = my_strcat(cmd, tab[0]);
        r = execve(cmd, tab, env);
    }
    free_tab(paths);
    return r;
}

int next_main(char **tab, char **env, int status, uid_t original_euid)
{
    int pid = fork();
    int r = 0;

    if (pid == 0) {
        r = execute(tab, env, r);
        if (r == -1) {
            perror("execve failed");
            return 84;
        }
        return 0;
    } else
        waitpid(pid, &status, 0);
    if (WIFSIGNALED(status))
        return 84;
    if (seteuid(original_euid) != 0) {
        perror("seteuid restore failed");
        return 84;
    }
    return 0;
}

int main(int ac, char **av, char **env)
{
    char **tab = NULL;
    int status = 0;
    cap_t caps = cap_get_proc();
    cap_value_t cap_list[1] = {CAP_SETUID};
    uid_t original_euid = getuid();

    if (ac == 1 || !authenticate())
        return 84;
    cap_free(caps);
    if (seteuid(0) != 0) {
        perror("seteuid failed");
        return 84;
    }
    tab = malloc(sizeof(char *) * ac);
    for (int i = 1; av[i]; i++)
        tab[i - 1] = av[i];
    tab[ac - 1] = NULL;
    return next_main(tab, env, status, original_euid);
}
