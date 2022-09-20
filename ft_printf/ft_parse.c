/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minwcho <minwcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:29:32 by minwcho           #+#    #+#             */
/*   Updated: 2022/08/30 18:12:36 by minwcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	ft_parse_bonus(char *str, t_format f)
{
	while (*str != '.' && !ft_strchr(SPECIFIERS, *str))
	{
		if (*str == '+')
			f.plus = 1;
		if (*str == ' ')
			f.space = 1;
		if (*str == '#')
			f.sharp = 1;
		str++;
	}
	return (f);
}

t_format	ft_parse_width(char *str, va_list ap, t_format f)
{
	int	specified;

	specified = 0;
	while (*str != '.' && !ft_strchr(SPECIFIERS, *str))
	{
		if (*str == '-')
			f.minus = 1;
		if (*str == '0' && !ft_isdigit(*(str - 1))) //0이 오면
			f.zero = 1;
		else if (((*str > '0' && *str <= '9') || *str == '*') && !specified)
		{
			if (*str == '*')
				f.width = va_arg(ap, int); //int형의 인자를 길이로서 가져오기
			else
				f.width = ft_atoi(str); //길이 저장
			specified = 1;
		}
		str++;
	}
	return (f);
}

t_format	ft_parse_precision(char *str, va_list ap, t_format f)
{
	int	specified;

	specified = 0;
	while (!ft_strchr(SPECIFIERS, *str))
	{
		if ((ft_isdigit(*str) || *str == '*') && !specified) //숫자나 *가 오면
		{
			if (*str == '*')
				f.precision = va_arg(ap, int); //int형의 인자를 정밀도로서 가져오기
			else
				f.precision = ft_atoi(str); //정밀도 저장
			specified = 1;
		}
		str++;
	}
	return (f);
}

int	ft_parse(char *str, va_list ap) //길이, 정밀도, 타입 등 파싱
{
	t_format	new_format;

	new_format = ft_parse_width(str, ap, ft_newformat()); //출력할 길이 파싱
	new_format = ft_parse_bonus(str, new_format); //보너스 파싱
	while (!ft_strchr(SPECIFIERS, *str) && *str != '.')
		str++;
	if (*str == '.' && !new_format.specifier) //정밀도가 있으면
	{
		new_format.dot = 1;
		new_format = ft_parse_precision(++str, ap, new_format); //정밀도 파싱
		while (!ft_strchr(SPECIFIERS, *str)) //반복문 끝난 후에 가리키는 주소값 = 타입이름
			str++;
	}
	if (new_format.width < 0) //길이 음수인지 양수인지 파싱
	{
		new_format.minus = 1;
		new_format.width *= -1;
	}
	new_format.specifier = *str; //타입 파싱
	new_format.neg_prec = new_format.precision < 0; //정밀도 음수인지 양수인지 파싱
	return (ft_print_format(new_format, ap)); //타입에 따라 출력해주기
}
