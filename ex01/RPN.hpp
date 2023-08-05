/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spapyan <spapyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:20:57 by spapyan           #+#    #+#             */
/*   Updated: 2023/08/04 16:20:57 by spapyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <stack>
#include <stdexcept>

class RPN {
public:
    typedef int result_type;

    static result_type resolveExpression(const std::string &line);

private:
    typedef result_type token_type;
    typedef unsigned char   op_type;

    RPN();
    ~RPN();
    RPN(const RPN &rhs);
    RPN& operator=(const RPN &rhs);

    static std::stack<token_type> stack_;

    static const int op_size = 4;
    static const struct operations {
        op_type symbol;
        token_type (*calc)(const token_type &lhs, const token_type &rhs);
    } operations_[op_size];

    static void popOperandsTokens(token_type &lhs, token_type &rhs);
    static void pushToken(token_type token);

    static void operate(op_type symbol);

    static token_type opSum(const token_type &lhs, const token_type &rhs);
    static token_type opSub(const token_type &lhs, const token_type &rhs);
    static token_type opMul(const token_type &lhs, const token_type &rhs);
    static token_type opDiv(const token_type &lhs, const token_type &rhs);
};