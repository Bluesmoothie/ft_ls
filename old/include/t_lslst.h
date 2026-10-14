/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:04:08 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 11:12:33 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LSLST_H
# define T_LSLST_H

# include <stdlib.h>
# include <time.h>
# include "libft.h"

typedef struct s_lslst		t_lslst;
typedef struct timespec		t_timespec;

typedef struct s_align_sizes
{
	size_t	links;
	size_t	owner;
	size_t	group;
	size_t	size;
	size_t	time;
}	t_align_sizes;

typedef struct s_lslst
{
	char			*name;
	char			mode;
	char			perms[10];
	char			*links;
	char			*owner;
	char			*group;
	char			*size;
	char			*time;
	t_timespec		mtime;
	t_align_sizes	sizes;
	t_lslst			*next;
}	t_lslst;

enum	e_lstmodes
{
	MLS2_FILE = '-',
	MLS2_DIR = 'd',
	MLS2_LNK = 'l',
	MLS2_INVALID = ' '
};

//	t_lslst.c
t_lslst			*ft_lslstnew(char *name);
void			ft_lslstadd_back(t_lslst **lst, t_lslst *new);
t_lslst			*ft_lslstlast(t_lslst *lst);
int				ft_lslstsize(t_lslst *lst);
void			ft_lslstclear(t_lslst **lst, void (*del)(void*));

//	t_lslst2.c
void			ft_lslstdelone(t_lslst *lst, void (*del)(void*));

#endif