#include "../Vector3.hpp"

Vector3::Vector3() : x(0.0), y(0.0), z(0.0)
{
	this->v3simd = _mm256_setzero_pd();
}
Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z)
{
	this->v3simd = _mm256_set_pd(this->x, this->y, this->z, 0.0);
}
Vector3::Vector3(Vector3&& other) : x(other.x), y(other.y), z(other.z)
{
	this->v3simd = _mm256_set_pd(this->x, this->y, this->z, 0.0);
}

Vector3::Vector3(double&& x, double&& y, double&& z) : x(x), y(y), z(z)
{
	this->v3simd = _mm256_set_pd(this->x, this->y, this->z, 0.0);
}
Vector3::Vector3(const double& x, const double& y, const double& z) : x(x), y(y), z(z)
{
	this->v3simd = _mm256_set_pd(this->x, this->y, this->z, 0.0);
}


void	Vector3::Add(const Vector3& other) noexcept
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->v3simd = _mm256_set_pd(this->x, this->y, this->z, 0.0);
}

Vector3	Vector3::SIMDCross(const Vector3& other) const noexcept
{
	double256	thisPermuted	= _mm256_permute4x64_pd(this->v3simd, _MM_SHUFFLE(3, 0, 2, 1));
	double256	otherPermuted	= _mm256_permute4x64_pd(other.v3simd, _MM_SHUFFLE(3, 1, 0, 2));
	double256	mul1			= _mm256_mul_pd(thisPermuted, otherPermuted);
	double256	result;
	Vector3		ret;
	thisPermuted = _mm256_permute4x64_pd(this->v3simd, _MM_SHUFFLE(3, 1, 0, 2));
	otherPermuted = _mm256_permute4x64_pd(other.v3simd, _MM_SHUFFLE(3, 0, 2, 1));
	result = _mm256_sub_pd(mul1, _mm256_mul_pd(thisPermuted, otherPermuted));
	ret.x = _mm256_cvtsd_f64(_mm256_permute4x64_pd(result, _MM_SHUFFLE(0, 0, 0, 0)));
	ret.y = _mm256_cvtsd_f64(_mm256_permute4x64_pd(result, _MM_SHUFFLE(1, 1, 1, 1)));
	ret.z = _mm256_cvtsd_f64(_mm256_permute4x64_pd(result, _MM_SHUFFLE(2, 2, 2, 2)));
	return (ret);
}
Vector3	Vector3::Cross(const Vector3& other) const noexcept
{
	return (Vector3(	this->y * other.z - this->z * other.y,
						this->z * other.x - this->x * other.z,
						this->x * other.y - this->y * other.x));
}

double Vector3::Norm() const noexcept
{
	return (sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
}
