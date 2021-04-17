#pragma once
#include <complex>

namespace Geometry
{

	template< typename T>
	struct Rectangle
	{
	public:
		Point<T> bottomLeftCorner_;
		Point<T> topRightCorner_;
	public:
		Rectangle() noexcept;
		Rectangle(T width, T height) noexcept;
		Rectangle(Point<T> topRightCorner) noexcept;
		Rectangle(Point<T> bottomLeftCorner, Point<T> topRightCorner) noexcept;
		Rectangle(T bottomLeftX, T bottomLeftY, T topRightX, T topRightY) noexcept;
		Rectangle(const Rectangle& rectangle) noexcept;
		Rectangle(std::complex<T> bottomLeftCorner, std::complex<T> topRightCorner) noexcept;
		Rectangle<T>& operator=(const Rectangle<T>& rectangle) noexcept;
		Rectangle<T>& operator=(const Rectangle<T>& rectangle) const noexcept;
		Rectangle operator+(const Point<T>& other) const noexcept;
		Rectangle operator*(const T other) const noexcept;
		Rectangle operator*(const Point<T>& other) const noexcept;
		inline Point<T> size() const noexcept;
		inline T sizeX() const noexcept;
		inline T sizeY() const noexcept;
		inline T area() const noexcept;
		std::string to_string(bool bottomLeftFirst = true) const noexcept;
		~Rectangle() = default;
	};

	template< typename T>
	Rectangle<T>::Rectangle() noexcept:
		bottomLeftCorner_{ Point<T>(0, 0) },
		topRightCorner_{ Point<T>(0, 0) }
	{
	}

	template< typename T>
	Rectangle<T>::Rectangle(T width, T height) noexcept:
		bottomLeftCorner_{ Point<T>(0, 0) },
		topRightCorner_{ Point<T>(width, height) }
	{
	}

	template< typename T>
	Rectangle<T>::Rectangle(Point<T> topRightCorner) noexcept:
		bottomLeftCorner_{ Point<T>(0, 0) },
		topRightCorner_{ topRightCorner }
	{
	}

	template< typename T>
	Rectangle<T>::Rectangle(Point<T> bottomLeftCorner, Point<T> topRightCorner) noexcept:
		bottomLeftCorner_{ bottomLeftCorner },
		topRightCorner_{ topRightCorner }
	{
	}

	template< typename T>
	Rectangle<T>::Rectangle(T bottomLeftX, T bottomLeftY, T topRightX, T topRightY) noexcept:
		bottomLeftCorner_{ bottomLeftX, bottomLeftY },
		topRightCorner_{ topRightX, topRightY }
	{
	}

	template< typename T>
	Rectangle<T>::Rectangle(const Rectangle& rectangle) noexcept:
		bottomLeftCorner_{ rectangle.bottomLeftCorner_ },
		topRightCorner_{ rectangle.topRightCorner_ }
	{
	}

	template< typename T>
	Rectangle<T>::Rectangle(std::complex<T> bottomLeftCorner, std::complex<T> topRightCorner) noexcept:
		bottomLeftCorner_{ bottomLeftCorner },
		topRightCorner_{ topRightCorner }
	{
	}

	template< typename T>
	Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& rectangle) noexcept
	{
		if (this != rectangle)
		{
			bottomLeftCorner_ = rectangle.width;
			topRightCorner_ = rectangle.topRightCorner_;
		}
		return this;
	}

	template< typename T>
	Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& rectangle) const noexcept
	{
		if (this != rectangle)
		{
			bottomLeftCorner_ = rectangle.width;
			topRightCorner_ = rectangle.topRightCorner_;
		}
		return this;
	}

	template< typename T>
	Rectangle<T> Rectangle<T>::operator+(const Point<T>& other) const noexcept
	{
		Rectangle result(bottomLeftCorner_ + other, topRightCorner_ + other);
		return result;
	}

	template< typename T>
	Rectangle<T> Rectangle<T>::operator*(const T other) const noexcept
	{
		Rectangle result(bottomLeftCorner_ * other, topRightCorner_ * other);
		return result;
	}

	template< typename T>
	Rectangle<T> Rectangle<T>::operator*(const Point<T>& other) const noexcept
	{
		Rectangle result(topRightCorner_.coordinates_[0] * other.coordinates_[0], topRightCorner_.coordinates_[1] * other.coordinates_[1]);
		return result;
	}

	template< typename T>
	inline Point<T> Rectangle<T>::size() const noexcept
	{
		return Point<T>(topRightCorner_.coordinates_[0] - bottomLeftCorner_.coordinates_[0], topRightCorner_.coordinates_[1] - bottomLeftCorner_.coordinates_[1]);
	}

	template< typename T>
	inline T Rectangle<T>::sizeX() const noexcept
	{
		return topRightCorner_.coordinates_[0] - bottomLeftCorner_.coordinates_[0];
	}

	template< typename T>
	inline T Rectangle<T>::sizeY() const noexcept
	{
		return topRightCorner_.coordinates_[1] - bottomLeftCorner_.coordinates_[1];
	}

	template< typename T>
	inline T Rectangle<T>::area() const noexcept
	{
		return sizeX() * sizeY();
	}

	template<typename T>
	inline std::string Rectangle<T>::to_string(bool bottomLeftFirst) const noexcept
	{
		std::string result;
		if (bottomLeftFirst)
		{
			result = bottomLeftCorner_.to_string() + " - " + topRightCorner_.to_string();
			return result;
		}

		result = topRightCorner_.to_string() + " - " + bottomLeftCorner_.to_string();
		return result;
	}

}