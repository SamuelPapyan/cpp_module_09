/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spapyan <spapyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:20:53 by spapyan           #+#    #+#             */
/*   Updated: 2023/08/07 20:26:11 by spapyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

#include <cctype> // std::isdigt(), std::isspace()

std::stack<RPN::token_type> RPN::stack_;

const struct RPN::operations RPN::operations_[op_size] = {
	{'+', &RPN::opSum},
	{'-', &RPN::opSub},
	{'*', &RPN::opMul},
	{'/', &RPN::opDiv}
};

RPN::result_type RPN::resolveExpression(const std::string &line)
{
	for (std::string::const_iterator it = line.begin(); it != line.end(); ++it) {
		if (std::isspace(*it))
			continue;
		else if (std::isdigit(*it))
			pushToken(static_cast<token_type>(*it - '0'));
		else
			operate(static_cast<op_type>(*it));
	}
	if (stack_.size() > 1)
		throw::std::runtime_error("Operations ended and stack has more than 1 item");
	result_type ret = stack_.top();
	stack_ = std::stack<token_type>();
	return ret;
}

void RPN::popOperandsTokens(token_type &lhs, token_type &rhs)
{
	if (stack_.size() < 2)
		throw std::runtime_error("RPN stack must have at less 2 items to do operations");
	rhs = stack_.top();
	stack_.pop();
	lhs = stack_.top();
	stack_.pop();
}

void RPN::pushToken(token_type token)
{
	stack_.push(token);
}

void RPN::operate(op_type symbol)
{
	for (short i = 0; i < op_size; ++i) {
		if (operations_[i].symbol == symbol) {
			token_type lhs = 0, rhs = 0;
			popOperandsTokens(lhs, rhs);
			token_type res = (*(operations_[i].calc))(lhs, rhs);
			pushToken(res);
			return;
		}
	}
	throw std::runtime_error("Encoutered an undefined operator");
}

RPN::token_type RPN::opSum(const token_type &lhs, const token_type &rhs)
{
	return lhs + rhs;
}
RPN::token_type RPN::opSub(const token_type &lhs, const token_type &rhs)
{
	return lhs - rhs;
}
RPN::token_type RPN::opMul(const token_type &lhs, const token_type &rhs)
{
	return lhs * rhs;
}
RPN::token_type RPN::opDiv(const token_type &lhs, const token_type &rhs)
{
	if (rhs == 0)
		throw std::runtime_error("Tried to divide by 0");
	return lhs / rhs;
}