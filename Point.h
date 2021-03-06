#pragma once
#include <array>
#include <string>

namespace Geometry
{

	template< typename T, int dimensions = 2 >
	struct Point
	{
	public:
		std::array< T, dimensions > coordinates_;
	public:
		Point() noexcept;
		Point(T other) noexcept;
		Point(T x, T y) noexcept;
		Point(T x, T y, T z) noexcept;
		Point(const Point<T, dimensions>& other) noexcept;
		Point(const Point<T, dimensions>&& other) noexcept;
		~Point();

		Point<T, dimensions>& operator=(Point<T, dimensions>& other) noexcept;
		Point<T, dimensions>& operator=(Point<T, dimensions>&& other) noexcept;
		Point<T, dimensions> operator+(const Point<T, dimensions>& other) noexcept;
		Point<T, dimensions> operator+(const Point<T, dimensions>& other) const noexcept;
		Point<T, dimensions> operator-(const Point<T, dimensions>& other) noexcept;
		Point<T, dimensions> operator*(const Point<T, dimensions>& other) noexcept;
		Point<T, dimensions> operator/(T divisor);
		Point<T, dimensions> operator/(const Point<T, dimensions>& other) const;
		std::string to_string(bool point = true) const noexcept;
	};

	using Pixel = Point<int>;
	using ComplexPoint = Point<double>;

	template< typename T, int dimensions>
	Point<T, dimensions>::Point() noexcept
	{
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			coordinates_[index] = 0;
		}
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions>::Point(T other) noexcept
	{
		coordinates_[0] = other;
		if (dimensions > 1)
		{
			for (size_t index = 1; index < dimensions; ++index)
			{
				coordinates_[index] = 0;
			}
		}
	}

	template< typename T, int dimensions>
	Point<T, dimensions>::Point(T x, T y) noexcept
	{
		coordinates_[0] = x;
		coordinates_[1] = y;
	}

	template< typename T, int dimensions>
	Point<T, dimensions>::Point(T x, T y, T z) noexcept
	{
		coordinates_[0] = x;
		coordinates_[1] = y;
		coordinates_[2] = z;
	}

	template< typename T, int dimensions>
	Point<T, dimensions>::Point(const Point& other) noexcept:
		coordinates_{ other.coordinates_ }
	{
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions>::Point(const Point<T, dimensions>&& other) noexcept:
		coordinates_{ std::move(other.coordinates_) }
	{
	}

	template< typename T, int dimensions>
	Point<T, dimensions>::~Point()
	{
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions>& Point<T, dimensions>::operator=(Point<T, dimensions>& other) noexcept
	{
		if (this != &other)
		{
			for (size_t index = 0; index < coordinates_.size(); ++index)
			{
				coordinates_[index] = other.coordinates_[index];
			}
		}
		return *this;
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions>& Point<T, dimensions>::operator=(Point<T, dimensions>&& other) noexcept
	{
		if (this != &other)
		{
			for (size_t index = 0; index < coordinates_.size(); ++index)
			{
				coordinates_[index] = other.coordinates_[index];
			}
		}
		return *this;
	}

	template<typename T, int dimensions>
	Point<T, dimensions> Point<T, dimensions>::operator+(const Point<T, dimensions>& other) noexcept
	{
		Point<T, dimensions> result;
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			result.coordinates_[index] = coordinates_[index] + other.coordinates_[index];
		}
		return result;
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions> Point<T, dimensions>::operator+(const Point<T, dimensions>& other) const noexcept
	{
		Point<T, dimensions> result;
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			result.coordinates_[index] = coordinates_[index] + other.coordinates_[index];
		}
		return result;
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions> Point<T, dimensions>::operator-(const Point<T, dimensions>& other) noexcept
	{
		Point<T, dimensions> result;
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			result.coordinates_[index] = coordinates_[index] - other.coordinates_[index];
		}
		return result;
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions> Point<T, dimensions>::operator*(const Point<T, dimensions>& other) noexcept
	{
		Point<T, dimensions> result;
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			result.coordinates_[index] = coordinates_[index] * other.coordinates_[index];
		}
		return result;
	}

	template<typename T, int dimensions>
	Point<T, dimensions> Point<T, dimensions>::operator/(T divisor)
	{
		Point<T, dimensions> result;
		if (divisor != 0)
		{
			for (size_t index = 0; index < coordinates_.size(); ++index)
			{
				result.coordinates_[index] = coordinates_[index] / divisor;
			}
		}
		return result;
	}

	template<typename T, int dimensions>
	inline Point<T, dimensions> Point<T, dimensions>::operator/(const Point<T, dimensions>& other) const
	{
		Point<T, dimensions> result;
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			if (other.coordinates_[index] != 0)
			{
				result.coordinates_[index] = coordinates_[index] / other.coordinates_[index];
			}
		}

		return result;
	}

	template<typename T, int dimensions>
	inline std::string Point<T, dimensions>::to_string(bool point) const noexcept
	{
		std::string result = "";
		std::string prefix = "";
		std::string postfix = "";
		for (size_t index = 0; index < coordinates_.size(); ++index)
		{
			result += std::to_string(coordinates_[index]);
			if (index < coordinates_.size() - 1)
			{
				if (point) result += ", ";
				else result += "x";
			}
		}

		if (point)
		{
			prefix = "(";
			postfix = ")";
		}
		else
		{
			prefix = "[";
			postfix = "]";
		}

		result = prefix + result + postfix;
		return result;
	}

}