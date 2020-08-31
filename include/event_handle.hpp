/*
 * event_handle.hpp
 *
 *  Created on: Aug 19, 2020
 *      Author: benny
 */

#ifndef OBSERVERS_EVENT_HANDLE_HPP_
#define OBSERVERS_EVENT_HANDLE_HPP_

#include <memory>
#include <string>

namespace observers {

template <typename TSubject>
class EventHandle{

private:

    struct AbstractHandle {
        virtual ~AbstractHandle() = default;

        // TODO: replace with user defined events
        virtual void notify(std::string const & message) const = 0;
    };

    template <typename TObserver>
    struct HandleImplementation : public AbstractHandle {
    	TObserver & observer;

        HandleImplementation(TObserver & observer_) : observer(observer_){}
        virtual ~HandleImplementation() = default;

        // TODO: replace with user defined events
        virtual void notify(std::string const & message) const override {
        	observer.template notify<TSubject>(message);
        }

    };

    std::unique_ptr<AbstractHandle> impl;

public:

    template <typename TObserver>
    explicit EventHandle(TObserver & observer)
	: impl(std::make_unique<HandleImplementation<TObserver> >(observer)){
    	// Make sure the TObserver observes 'TSubject'
    	static_assert(TObserver::template observes_subject<TSubject>());
    }

    void notify(std::string const & message) const {
        impl->notify(message);
    }

};

} // namespace observers



#endif /* OBSERVERS_EVENT_HANDLE_HPP_ */
