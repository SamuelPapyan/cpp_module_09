/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spapyan <spapyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:30:44 by spapyan           #+#    #+#             */
/*   Updated: 2023/08/04 15:30:44 by spapyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Invalid number of arguments.\n";
        std::cerr << "Usage: " << argv[0] << " [input_file]\n";
        return 1;
    }

    BitcoinExchange exchange("data.csv");
    exchange.processInput(argv[1]);

    return 0;
}