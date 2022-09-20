/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minwcho <minwcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:29:12 by minwcho           #+#    #+#             */
/*   Updated: 2022/09/05 20:54:24 by minwcho          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		print_len;
	va_list	ap; //가변인자
	print_len = 0;
	va_start(ap, str);  //처음 고정된 인자의 주소값 넣기(va_arg로 다음 인자 주소값으로 초기화 가능)
	while (*str)
	{
		if (*str == '%')
		{
			if (*(++str))
				print_len += ft_parse((char *)str, ap); //파싱
			while (*str && !ft_strchr(SPECIFIERS, *str))
				str++;
		}
		else
			print_len += ft_printchar(*str); //바로 출력해줘야하므로 출력
		if (*str)
			str++;
	}
	va_end(ap); //가변인자를 쓴 후 무조건 프로그램 끝날 때 end
	return (print_len);
}

int	ft_print_format(t_format f, va_list ap)
{
	int	print_len;

	print_len = 0;
	if (f.specifier == 'c' || f.specifier == '%')
		print_len = ft_print_c_pct(f, ap);
	if (f.specifier == 's')
		print_len = ft_print_s(f, ap);
	if (f.specifier == 'u')
		print_len = ft_print_u(f, ap);
	if (f.specifier == 'd' || f.specifier == 'i')
		print_len = ft_print_d_i(f, ap);
	if (f.specifier == 'X' || f.specifier == 'x')
		print_len = ft_print_x(f, ap);
	if (f.specifier == 'p')
		print_len = ft_print_p(f, ap);
	return (print_len);
}

#include <stdio.h>

int main()
{
	ft_printf("%4d", 123);
	printf("%4d", 123);
}