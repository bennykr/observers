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

namespace observers {

void assert_with_message(bool condition, std::string const & message){
    assert( ((void) message, condition) );
}

} // namespace observers

#endif /* OBSERVERS_LOGGING_HPP_ */
