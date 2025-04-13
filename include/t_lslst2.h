/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst22.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:05:19 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 19:49:59 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LSLST2_H
# define T_LSLST2_H

# include <stdlib.h>

typedef struct s_lslst2	t_lslst2;

typedef struct s_lslst2
{
	char		*name;
	char		mode;
	char		perms[10];
	int			links;
	char		*owner;
	char		*group;
	int			size;
	t_lslst2	*next;
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

#endif