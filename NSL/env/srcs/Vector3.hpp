#ifndef NSL_VECTOR3_HPP
#define NSL_VECTOR3_HPP

# include <cmath>
# include "TypesCap.hpp"
# include "../SIMDplatform.h"
# include "../platform.h"

class Vector3
{
public:
	Vector3();
	Vector3(Vector3&&);
	Vector3(const Vector3&);
	Vector3(double&&, double&& = 0.0, double&& = 0.0);
	Vector3(const double&, const double& = 0.0, const double& = 0.0);

	void	Add(const Vector3& other) noexcept;
	Vector3	SIMDCross(const Vector3& other) const noexcept;
	Vector3	Cross(const Vector3& other) const noexcept;
	double	Norm() const noexcept;

public:
	double		x;
	double		y;
	double		z;

private:
	// 0 : x
	// 1 : y
	// 2 : z
	// 3 : w
	double256	v3simd;
};

/*typedef Vector3<int8>	Vector3c;
typedef Vector3<int16>	Vector3s;
typedef Vector3<int32>	Vector3i;
typedef Vector3<int64>	Vector3l;

typedef Vector3<uint8>	Vector3uc;
typedef Vector3<uint16>	Vector3us;
typedef Vector3<uint32>	Vector3ui;
typedef Vector3<uint64>	Vector3ul;

typedef Vector3<float>	Vector3f;
typedef Vector3<double>	Vector3d;*/

#endif
