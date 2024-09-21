#ifndef NSL_SIMDPLATFORM_H
#define NSL_SIMDPLATFORM_H

# if defined(__x86_64__) || defined(__amd64__) 							// ifAMD/Intel/ARM
#  define INTEL
#  if defined(__MMX__)	// ifMMX
#   define MMX
#  endif				// endMMX

#  if defined(__SSE_4_2__)	// ifSSE
#   define SSE4_2
#  endif
#  if defined(__SSE_4_1__)
#   define SSE4_1
#  endif
#  if defined(__SSSE3__)
#   define SSSE3
#  endif
#  if defined(__SSE3__)
#   define SSE3
#  endif
#  if defined(__SSE2__)
#   define SSE2
#  endif
#  if defined(__SSE__)
#   define SSE
#  endif					// endSSE

#  if defined(__AVX512VL__)		// ifAVX
#   define AVX512VL
#  endif
#  if defined(__AVX512BW__)
#   define AVX512BW
#  endif
#  if defined(__AVX512DQ__)
#   define AVX512DQ
#  endif
#  if defined(__AVX512CD__)
#   define AVX512CD
#  endif
#  if defined(__AVX512F__)
#   define AVX512F
#  endif
#  if defined(__AVX2__)
#   define AVX2
#  endif
#  if defined(__AVX__)
#   define AVX
#  endif						// endAVX

#  if defined(__FMA__)	// ifFMA
#   define FMA
#  endif				// endFMA

# elif defined(__arm__) || defined(__ARM__) || defined(__aarch64__)
#  define ARM
#  if defined(__ARM_NEON__)
#   define NEON
#  endif
# elif defined(__riscv)
#  define RISCVPROC
#  if defined(__riscv_vector)
#   define RISCVSIMD
#  endif
# endif																	// endAMD/Intel/ARM

# include <iostream>
extern void	print_compatibleSIMD()
{
#if defined(INTEL)
	std::cout << "\n\tIntel Processor: " << std::endl;
# if defined(SSE4_2)
	std::cout << "sse4.2" << std::endl;
# endif
# if defined(SSE4_1)
	std::cout << "sse4.1" << std::endl;
# endif
# if defined(SSSE3)
	std::cout << "ssse3" << std::endl;
# endif
# if defined(SSE3)
	std::cout << "sse3" << std::endl;
# endif
# if defined(SSE2)
	std::cout << "sse2" << std::endl;
# endif
# if defined(SSE)
	std::cout << "sse" << std::endl;
# endif
# if defined(MMX)
	std::cout << "mmx" << std::endl;
# endif
# if defined(AVX512VL)
	std::cout << "AVX512VL" << std::endl;
# endif
# if defined(AVX512BW)
	std::cout << "AVX512BW" << std::endl;
# endif
# if defined(AVX512DQ)
	std::cout << "AVX512DQ" << std::endl;
# endif
# if defined(AVX512CD)
	std::cout << "AVX512CD" << std::endl;
# endif
# if defined(AVX512F)
	std::cout << "AVX512F" << std::endl;
# endif
# if defined(AVX2)
	std::cout << "AVX2" << std::endl;
# endif
# if defined(AVX)
	std::cout << "AVX" << std::endl;
# endif
# if defined(FMA)
	std::cout << "FMA" << std::endl;
# endif
#elif defined(ARM)
	std::cout << "\n\tARM Processor: " << std::endl;
# if defined(NEON)
	std::cout << "Neon" << std::endl;
# endif
#elif defined(RISCVPROC)
# if defined(RISCVSIMD)
	std::cout << "Riscv" << std::endl;
# endif
#endif
}

#endif
