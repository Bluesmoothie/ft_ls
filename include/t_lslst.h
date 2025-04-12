/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:05:19 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 00:26:38 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LSLST_H
# define T_LSLST_H

# include <stdlib.h>

typedef struct s_lslst	t_lslst;

typedef struct s_lslst
{
	char	*raw_arg;
	int		mode;
	t_lslst	*next;
}	t_lslst;

enum	e_modes
{
	MLS_INVALID,
	MLS_FILE,
	MLS_DIRECTORY
};

//	t_lslst.c
t_lslst		*ft_lslstnew(char *raw_arg);
void		ft_lslstadd_back(t_lslst **lst, t_lslst *new);
t_lslst		*ft_lslstlast(t_lslst *lst);
int			ft_lslstsize(t_lslst *lst);
void		ft_lslstclear(t_lslst **lst, void (*del)(void*));

#endif