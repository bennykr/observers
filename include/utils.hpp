/*
 * utils.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_UTILS_HPP_
#define OBSERVERS_UTILS_HPP_

#include <type_traits>

namespace observers::utils {

    template<typename T, typename... Ts>
    constexpr bool is_type_in_list(){
        return (... || std::is_same_v<T, Ts>);
    }
    

    template<typename First, typename... Next>
    constexpr bool unique_list(){
        if constexpr (0u == sizeof...(Next)){
            return true;
        } else {
            if constexpr (is_type_in_list<First, Next...>()){
                return false;
            } else {
                return unique_list<Next...>();
            }
        }
    }

    template<typename T, typename... Ts>
    constexpr size_t count_type_in_list(){
        return (... + std::is_same_v<T, Ts>);
    }

    template<typename T, typename First, typename... Next>
    constexpr size_t index_in_list(){
        static_assert(1u == count_type_in_list<T, First, Next...>());
        
        if constexpr (std::is_same_v<T, First>) {
            return 0u;
        } else {
            static_assert(sizeof...(Next) > 0u);
            return 1u + index_in_list<T, Next...>();
        }
    }

} // namespace observers::utils



#endif /* OBSERVERS_UTILS_HPP_ */
