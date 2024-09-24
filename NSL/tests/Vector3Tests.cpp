#include "Vector3Tests.hpp"

int	_mm_ez = 0;

double percentage(double a, double b)
{
    return ((a - b) / abs(a)) * 100.0;
}

void	Benchmark_Vector3_AVX(bool ez)
{
	std::cout << "\nBenchmark Vector3 -->" << std::endl;
	constexpr int num_vectors = 30000000;
	std::vector<Vector3> vectors(num_vectors);

	auto start_sse = std::chrono::high_resolution_clock::now();
	//for (Vector3& ez : vectors)
	//	ez = ez.SIMDCross(ez);
	auto end_sse = std::chrono::high_resolution_clock::now();

	auto start_basic = std::chrono::high_resolution_clock::now();
	for (Vector3& ez : vectors)
		ez = ez.Cross(ez);
	auto end_basic = std::chrono::high_resolution_clock::now();

	if (ez)
	{
		std::chrono::duration<float> duration_sse = end_sse - start_sse;
		std::chrono::duration<float> duration_basic = end_basic - start_basic;
		float sseTime = duration_sse.count();
		float basicTime = duration_basic.count();
		std::cout << "SSE: " << sseTime << std::endl;
		std::cout << "Basic: " << basicTime << std::endl;

		int perfTime;
		if (basicTime < sseTime)
			perfTime = -percentage(sseTime, basicTime);
		else if (basicTime > sseTime)
			perfTime = percentage(basicTime, sseTime);
		else
			perfTime = 0;
		_mm_ez += perfTime;
		std::cout << "\e[1mPerf: "
		<<
			perfTime
		<< "%\e[0m" <<
		std::endl;
	}
}
