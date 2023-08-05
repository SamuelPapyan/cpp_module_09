/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spapyan <spapyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:30:39 by spapyan           #+#    #+#             */
/*   Updated: 2023/08/04 15:30:39 by spapyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

class BitcoinExchange {
public:
    BitcoinExchange(const std::string &filename);
    void processInput(const std::string &filename);

private:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &rhs);

    std::map<std::string, double> data_;
    double  getExchangeRate(const std::string &date);
    bool    validateDate(const std::string &date);
    bool    validateValue(const double &value);
};


