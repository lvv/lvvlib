// MEMOIZE() from http://slackito.com/2011/03/17/automatic-memoization-in-cplusplus0x/

				#ifndef  LVV_MEMOIZE_H
				#define  LVV_MEMOIZE_H

				#include <functional>
				#include <map>
				namespace lvv {


		template <typename ReturnType, typename... Args>
		std::function<ReturnType (Args...)>
memoize (std::function<ReturnType (Args...)> func)  {

	std::map<std::tuple<Args...>, ReturnType> cache;

	return ([=](Args... args) mutable   {
        	std::tuple<Args...> t(args...);
        	if (cache.find(t) == cache.end())                
        		cache[t] = func(args...);
        	return cache[t];
	});
}


				};  // namespace lvv
				#endif // LVV_MOMOIZE_H

