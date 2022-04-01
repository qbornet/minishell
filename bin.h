#ifndef BIN_H
# define BIN_H
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int		ft_pwd(void);
int		ft_echo(const char *s, int flag);
int		ft_cd(const char *path);
int		ft_export(char *var, char ***env_curr);
int		ft_unset(char *var, char ***env_curr);

#endif
