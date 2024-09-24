#include "../Vector3.hpp"

Vector3::Vector3() : x(0.0), y(0.0), z(0.0), w(0.0)
{
}
Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z), w(0.0)
{
}
Vector3::Vector3(Vector3&& other) : x(other.x), y(other.y), z(other.z), w(0.0)
{
}

Vector3::Vector3(double&& x, double&& y, double&& z) : x(x), y(y), z(z), w(0.0)
{
}
Vector3::Vector3(const double& x, const double& y, const double& z) : x(x), y(y), z(z), w(0.0)
{
}


void	Vector3::Add(const Vector3& other) noexcept
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

#if defined(AVX2)
Vector3	Vector3::Cross(const Vector3& other) const noexcept
{
	double256	vA		= _mm256_load_pd(&this->x);
	double256	vB		= _mm256_load_pd(&other.x);
	double256	a_vYZX	= _mm256_permute4x64_pd(vA, _MM_SHUFFLE(3, 1, 2, 0));
	double256	a_vZXY	= _mm256_permute4x64_pd(vA, _MM_SHUFFLE(3, 2, 0, 1));
	double256	b_vYZX	= _mm256_permute4x64_pd(vB, _MM_SHUFFLE(3, 1, 2, 0));
	double256	b_vZXY	= _mm256_permute4x64_pd(vB, _MM_SHUFFLE(3, 2, 0, 1));
	Vector3		ret;
	_mm256_store_pd(static_cast<double*>(&ret.x),
					_mm256_sub_pd(	_mm256_mul_pd(a_vYZX, b_vZXY),
									_mm256_mul_pd(a_vZXY, b_vYZX)
								)
					);
	return (ret);
}
#else
Vector3	Vector3::Cross(const Vector3& other) const noexcept
{
	return (Vector3(this->y * other.z - this->z * other.y,
					this->z * other.x - this->x * other.z,
					this->x * other.y - this->y * other.x));
}
#endif

double Vector3::Norm() const noexcept
{
	return (sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
}
