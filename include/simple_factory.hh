#ifndef SIMPLE_FACTORY_HH_
#define SIMPLE_FACTORY_HH_

// code borrowed from https://github.com/Enhex/Factory

#include <memory>
#include <unordered_map>

// Factory used to create instances of registered types derived from base
template<typename Base, typename Key, typename... Ts>
struct SimpleFactory
{
	// create instance
	static std::unique_ptr<Base> create(Key const& key, Ts... args)
	{
		auto iter = get_map().find(key);
		if (iter == get_map().end())
			return nullptr;
		// call factory function
		return iter->second(args...);
	}

	using map_type = std::unordered_map<Key, std::unique_ptr<Base>(*)(Ts...)>;

	// singleton to guarentee initialization in other translation units
	static map_type& get_map() {
		static map_type map;
		return map;
	}
};

#if __cplusplus == 201103L
namespace std {
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}
#endif

// Registers a factory function for creating a type derived from base
template<typename Base, typename Key, typename Derived, typename... Ts>
struct Register {
	Register(Key const& name) {
		SimpleFactory<Base, Key, Ts...>::get_map()[name] = &create_base;
	}

	// used for a pointer to factory function
	static std::unique_ptr<Base> create_base(Ts... args) {
		return std::make_unique<Derived>(args...);
	}
};

#endif // SIMPLE_FACTORY_HH_
