#ifndef NSL_VECTOR3_HPP
#define NSL_VECTOR3_HPP

# include <cmath>
# include "TypesCap.hpp"
# include "../SIMDplatform.h"
# include "../platform.h"

class alignas(32) Vector3
{
public:
	Vector3();
	Vector3(Vector3&&);
	Vector3(const Vector3&);
	Vector3(double&&, double&& = 0.0, double&& = 0.0);
	Vector3(const double&, const double& = 0.0, const double& = 0.0);

	void	Add(const Vector3& other) noexcept;
	Vector3	Cross(const Vector3& other) const noexcept;
	double	Norm() const noexcept;

public:
	double	x;
	double	y;
	double	z;

private:
	double	w;

public:
	Vector3&	operator=(const Vector3& o)
	{
#if defined(AVX2)
		_mm256_store_pd(&this->x, _mm256_load_pd(&o.x));
#else
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
#endif
		return (*this);
	}
};

#endif
