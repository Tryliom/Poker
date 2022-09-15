#pragma once


namespace Utils
{
	/**
	 * @brief Clear the console.
	 */
	void ClearConsole();

	/**
	 * \brief Remove an object from the vector
	 * \tparam T A class defined in the vector
	 * \param vector The vector to remove the object from
	 * \param element The object to remove
	 */
	template <typename T>
	void Remove(std::vector<T>& vector, const T& element)
	{
		vector.erase(vector.begin(), vector.end(), element);
	}
}
