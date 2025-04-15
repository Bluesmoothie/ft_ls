/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:04:08 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 18:24:41 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LSLST2_H
# define T_LSLST2_H

# include <stdlib.h>
# include <time.h>
# include "libft.h"

typedef struct s_lslst2		t_lslst2;

typedef struct s_align_sizes
{
	size_t	links;
	size_t	owner;
	size_t	group;
	size_t	size;
	size_t	time;
}	t_align_sizes;

typedef struct s_lslst2
{
	char			*name;
	char			mode;
	char			perms[10];
	char			*links;
	char			*owner;
	char			*group;
	char			*size;
	char			*time;
	t_align_sizes	sizes;
	t_lslst2		*next;
}	t_lslst2;

enum	e_lst2modes
{
	MLS2_FILE = '-',
	MLS2_DIR = 'd',
	MLS2_LNK = 'l',
	MLS2_INVALID = ' '
};

//	t_lslst2.c
t_lslst2		*ft_lslst2new(char *name);
void			ft_lslst2add_back(t_lslst2 **lst, t_lslst2 *new);
t_lslst2		*ft_lslst2last(t_lslst2 *lst);
int				ft_lslst2size(t_lslst2 *lst);
void			ft_lslst2clear(t_lslst2 **lst, void (*del)(void*));

//	t_lslst22.c
void			ft_lslst2delone(t_lslst2 *lst, void (*del)(void*));

#endif