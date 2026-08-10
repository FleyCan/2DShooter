#pragma once

#include <cmath>
#include <cstddef>
#include <array>
#include <ostream>

template<typename T, std::size_t N>
struct Vector
	: std::array<T,N>
{ 
	friend
	Vector& operator+=(Vector& a, Vector const& b) {
		for(std::size_t i = 0; i < N; ++i) {
			a[i] += b[i];
		}
		return a;
	}

	friend
	Vector& operator-=(Vector& a, Vector const& b) {
		for(std::size_t i = 0; i < N; ++i) {
			a[i] -= b[i];
		}
		return a;
	}

	friend
	Vector& operator/=(Vector& vector,T const& skalar) {
		for(std::size_t i = 0; i < N; ++i) {
			vector[i] /= skalar;
		}
		return vector;
	}

	friend
	Vector& operator*=(Vector& vector,T const& skalar) {
		for(std::size_t i = 0; i < N; ++i) {
			vector[i] *= skalar;
		}
		return vector;
	}

	friend
	Vector operator+(Vector lhs, Vector const& rhs) {
		return lhs += rhs;
	}

	friend
	Vector operator-(Vector lhs, Vector const& rhs) {
		return lhs -= rhs;
	}

	friend
	Vector operator/(Vector vector,T const& skalar) {
		return vector /= skalar;
	}

	friend
	Vector operator*(Vector vector,T const& skalar) {
		return vector *= skalar;
	}

	friend
	Vector operator*(T const& skalar,Vector vector) {
		return vector *= skalar;
	}

	friend
	T operator*(Vector const& a, Vector const& b) {
		T sum{};
		for(std::size_t i = 0; i < N; ++i) {
			sum += a[i] * b[i];
		}
		return sum;
	}

	T length() const {
		return std::sqrt(*this**this);
	}

	T orientation() const
		requires(N == 2)
	{
		auto& self = *this;
		return std::atan2(self[1],self[0]);
	}

	static Vector polar(T length, T orientation)
		requires(N == 2)
	{
		return Vector{std::cos(orientation),std::sin(orientation)} * length;
	}

	Vector rotate(T radians) const
		requires(N == 2)
	{
		auto& self = *this;
		return Vector{
			  std::cos(radians) * self[0] - std::sin(radians) * self[1]
			, std::sin(radians) * self[0] + std::cos(radians) * self[1]
		};
	}

	Vector rotate_ortho() const
	requires(N == 2)
	{
		auto& self = *this;
		return Vector{
			  -self[1]
			,  self[0]
		};
	}

	friend
	std::ostream& operator<<(
		  std::ostream& os
		, Vector const& vector
	) {
		char sep{};
		os << '{';
		for(T const& element : vector) {
			os << sep << '{' << element << "}";
			sep = ',';
		}
		os << '}';
		return os;
	}
	
};


