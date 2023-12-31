/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spapyan <spapyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:30:29 by spapyan           #+#    #+#             */
/*   Updated: 2023/08/07 20:17:58 by spapyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

BitcoinExchange::BitcoinExchange(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (file.is_open() == false) {
        throw std::runtime_error("Error: " + filename + " can not be opened");
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::string::size_type delimiter_pos = line.find(',');
        if (delimiter_pos == std::string::npos) {
            std::cerr << "Error: Invalid format in database => "
                    << line << '\n';
            continue;
        }
        std::string date = line.substr(0, delimiter_pos);
        std::string rate_str = line.substr(delimiter_pos + 1);

        double rate;
        std::istringstream rate_stream(rate_str);
        if (!(rate_stream >> rate)) {
            std::cerr << "Error: Invalid rate format in database => "
                    << rate_str << "\n";
            continue;
        }
        data_[date] = rate;
    }
}

double BitcoinExchange::getExchangeRate(const std::string &date) {
    std::map<std::string, double>::iterator it = data_.lower_bound(date);
    if (it != data_.end()) {
        return it->second;
    } else if (!data_.empty()) {
        return (--it)->second;
    }

    return -1.0;
}

bool    BitcoinExchange::validateDate(const std::string& date) {
    std::string::size_type del1 = date.find('-');
    std::string::size_type del2 = date.rfind('-');

    if (del1 == std::string::npos || del1 == del2)
        return false;

    std::string year_str = date.substr(0, del1);
    std::string month_str = date.substr(del1 + 1, del2 - del1 - 1);
    std::string day_str = date.substr(del2 + 1);

    int year, month, day;
    std::istringstream year_ss(year_str), month_ss(month_str), day_ss(day_str);

    if (!(year_ss >> year) || !(month_ss >> month) || !(day_ss >> day))
        return false;
    
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        if (day > 30)
            return false;

    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28))
            return false;
    }

    return true;
}

bool    BitcoinExchange::validateValue(const double &value) {
    if (value < 0 || value > 1000) {
        std::cerr << "Error: Value "
                << value
                << " is not a positive number between 0 and 1000.\n";
        return false;
    }
    return true;
}

void    BitcoinExchange::processInput(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (file.is_open() == false) {
        throw std::runtime_error("Error: " + filename + " can not be opened");
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string date;
        double  value;
        char    delimiter;

        if (!(ss >> date >> delimiter >> value)) {
            std::cerr << "Error: Unable to parse line => "
                    << line << '\n';
            continue;
        }

        if (delimiter != '|') {
            std::cerr << "Error: Expected '|' delimiter in line => "
                    << line << '\n';
            continue;
        }
        if (!validateDate(date)) {
            std::cerr << "Error: Invalid date format in line => "
                    << line << '\n';
            continue;
        }
        if (!validateValue(value)) {
            continue;
        }

        double exchangeRate = getExchangeRate(date);
        if (exchangeRate == -1.0) {
            std::cerr << "Error: No exchange rate available for date => "
                    << date << '\n';
            continue;
        }

        std::cout << date << " => "
                << value << " = " << value * exchangeRate
                << '\n';
    }
}