#ifndef __BE_UTILS_GLOBALS_H__
#define __BE_UTILS_GLOBALS_H__

#include <bitset>

#ifndef MAX_NUM_COMPONENTS
#define MAX_NUM_COMPONENTS 32
#endif // !MAX_NUM_COMPONENTS

#if defined(_WIN64)
#define CACHE_LINE_SIZE 64
#else
#define CACHE_LINE_SIZE 32
#endif

namespace BE
{

using Signature = std::bitset<MAX_NUM_COMPONENTS>;

namespace Utils
{

inline std::size_t componentTypeId()
{
	static std::size_t next = 0;
	return next++;
}

template<typename T>
inline std::size_t componentTypeId()
{
	static std::size_t id = componentTypeId();
	return id;
}

inline std::size_t archtypeTypeId()
{
	static std::size_t next = 0;
	return next++;
}

template<typename T>
inline std::size_t archtypeTypeId()
{
	static std::size_t id = archtypeTypeId();
	return id;
}

}

template<typename ...Ts>
inline Signature genSignature()
{
	Signature signature;

	(..., signature.set(Utils::componentTypeId<Ts>()));

	return signature;
}

}

#endif // !__BE_UTILS_GLOBALS_H__
