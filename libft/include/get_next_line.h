/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:13:52 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 15:14:04 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 64

typedef struct		s_buf
{
	char			*text;
	int				fd;
	struct s_buf	*next;
}					t_buf;

int					get_next_line(const int fd, char **line);

#endif
