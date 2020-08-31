/*
 * logging.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_LOGGING_HPP_
#define OBSERVERS_LOGGING_HPP_

#include <string>
#include <cassert>
#include <iostream>

namespace observers {

inline void assert_with_message(bool condition, std::string const & message){
    if (!condition){
        std::cerr << message << std::endl;
        std::abort();
    }
}

} // namespace observers

#endif /* OBSERVERS_LOGGING_HPP_ */
