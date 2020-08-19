/*
 * utils.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_UTILS_HPP_
#define OBSERVERS_UTILS_HPP_

namespace observers::utils {

	template<typename T, typename... Ts>
	constexpr bool is_type_in_list(){
        return (... || std::is_same_v<T, Ts>);
    }

} // namespace observers::utils



#endif /* OBSERVERS_UTILS_HPP_ */
