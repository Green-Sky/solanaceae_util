#pragma once

#include <array>
#include <vector>
#include <cstddef>

template<typename EventI>
struct EventProviderI {
	using enumType = typename EventI::enumType;

	virtual ~EventProviderI(void) {};

	// TODO: unsub
	virtual void subscribe(EventI* object, const enumType event_type) {
		_subscribers.at(static_cast<size_t>(event_type)).push_back(object);
	}

	protected:
		template<typename T>
		bool dispatch(enumType event_type, const T& event) {
			for (auto* zei : _subscribers.at(static_cast<size_t>(event_type))) {
				if (zei->onEvent(event)) {
					return true;
				}
			}
			return false;
		}

	protected:
		std::array<
			std::vector<EventI*>,
			static_cast<size_t>(enumType::MAX)
		> _subscribers;
};

