#ifndef __BE_UTILS_CACHE_SET_H__
#define __BE_UTILS_CACHE_SET_H__

#include "Globals.h"

#include <cstddef>

namespace BE
{
namespace Utils
{

enum class CacheUtilization
{
	Full = 1,
	Half = 2,
	Quarter = 4
};

template<typename T, CacheUtilization CU = CacheUtilization::Full>
class CacheSet
{
public:
	// Calculate the number of elements that fit inside the cache (with cache utilization restriction)
	static constexpr std::size_t SetSize{ (CACHE_LINE_SIZE / static_cast<int>(CU) - sizeof(std::size_t)) / sizeof(T) };

	CacheSet() = default;
	~CacheSet() = default;

	// Copies the elements of other cache set to this cache set
	CacheSet<T, CU> &operator=(const CacheSet<T, CU> &other);

	// Inserts element inside cache set
	void insert(T element);
	// Removes element from cache set
	void remove(T element);
	// Checks if an element exists inside cache set
	bool contains(T element) const;
private:
	// Array of all elements
	T m_array[SetSize]{};
	// Number of elements inside cache set
	std::size_t m_numElements{ 0 };
};

template<typename T, CacheUtilization CU>
inline CacheSet<T, CU> &CacheSet<T, CU>::operator=(const CacheSet<T, CU> &other)
{
	// Copy the number of elements
	m_numElements = other.m_numElements;
	// Copy every element from other cache set to this cache set
	for (std::size_t i = 0; i < m_numElements; i++)
	{
		m_array[i] = other.m_array[i];
	}

	// Return the reference to this cache set
	return *this;
}

template<typename T, CacheUtilization CU>
inline void CacheSet<T, CU>::insert(T element)
{
	// If array is not full and array does not contain the element
	if (m_numElements < SetSize && !contains(element))
	{
		// Insert the element and increment the number of elements
		m_array[m_numElements++] = element;
	}
}

template<typename T, CacheUtilization CU>
inline void CacheSet<T, CU>::remove(T element)
{
	// Traverse the array in reverse order to find the index of the element to be removed
	std::size_t elementIndex = m_numElements - 1;
	while (elementIndex >= 0 && m_array[elementIndex] != element)
	{
		elementIndex--;
	}

	// If the element was found
	if (elementIndex >= 0)
	{
		// Replace the element with the last element of the array and decrement the number of elements
		m_array[elementIndex] = m_array[--m_numElements];
	}
}

template<typename T, CacheUtilization CU>
inline bool CacheSet<T, CU>::contains(T element) const
{
	// Traverse the array to find element in array
	for (std::size_t i = 0; i < m_numElements; i++)
	{
		if (m_array[i] == element)
		{
			return true;
		}
	}

	// If this point is reached then the elements is not in this cache set
	return false;
}

}
}

#endif // !__BE_UTILS_CACHE_SET_H__
