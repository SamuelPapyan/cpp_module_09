/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spapyan <spapyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:20:48 by spapyan           #+#    #+#             */
/*   Updated: 2023/08/04 16:20:48 by spapyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "RPN.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"OPERATION\"n";
        return 1;
    }

    try {
        int res = RPN::resolveExpression(argv[1]);
        std::cout << "Result: " << res << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}