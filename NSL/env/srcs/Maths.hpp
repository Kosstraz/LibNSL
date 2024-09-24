#ifndef NSL_MATHS_HPP
#define NSL_MATHS_HPP

# include "../platform.h"

namespace Maths
{

inline static constexpr double	Pi = 3.14159265359;

inline double	DegToRad(const double& deg)
{
	return (deg * (Maths::Pi / 180.0));
}

inline double	RadToDeg(const double& rad)
{
	return (rad * (180.0 / Maths::Pi));
}

}

#endif
