/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NEW_STANDARD_LIBRARY_H
#define NEW_STANDARD_LIBRARY_H

# include "NSLplatform.h"
# include "NSLSIMDplatform.h"

// !Two memory leaks in threading edge case (in the Thread class)
// !If not, no memory leak currently detected

// ?Similaire à std::allocator
# include "NSLsrcs/Allocator.hpp"

// ?A smart pointer, similar to std::shared_ptr<T>
# include "NSLsrcs/SmartPtr.hpp"

// ?Type capabilities (everything is calculated at compile time)
// Upcoming additions
# include "NSLsrcs/TypesCap.hpp"

// ?Allows to know the precise type
// ?Less precise on compilers other than GNU (GCC/clang/...)
# include "NSLsrcs/TypesName.hpp"

// ?Equivalent à std::is_base_of_v
# include "NSLsrcs/IsSubclassOf.hpp"

// ?Similaire à std::is_convertible_v
# include "NSLsrcs/IsConvertible.hpp"

// ?Constitutes a sort of heap of objects, of variable types, allocated
// To optimize
# include "NSLsrcs/Pool.hpp"

// ?Equivalent à std::cout/cin (version nulle)
// To optimize (a lot)
# include "NSLsrcs/IOStreams.hpp"

// ?Allows heavy mathematical calculations to be performed during compilation
# include "NSLsrcs/CompilationMaths.hpp"

// ?Equivalent à std::function
# include "NSLsrcs/Function.hpp"

// ?Packing a variadic argument | équivalent to std::tuple
# include "NSLsrcs/Package.hpp"

// ?Allows you to unpack a Package<...> and apply it to a given function
# include "NSLsrcs/Unpack.hpp"

// ?Equivalent à std::thread
// INFO:
// Please exit threads cleanly with Thread::Return(...), particularly if you need a return value
# include "NSLsrcs/Thread.hpp"

// ?You can send information between any threads [Channel::Send() & Channel::Receive<T>()]
# include "NSLsrcs/Channel.hpp"

// ?Equivalent à std::mutex (avec + de fonctionnalités)
# include "NSLsrcs/Mutex.hpp"

// ?Enables secure multithreading and easy access to threads via their identifier
# include "NSLsrcs/MultiThreading.hpp"

// ?Some utilities
# include "NSLsrcs/Memory.hpp"

// ?Equivalent à std::string (en beaucoup + performant & avec + de fonctionnalités)
// Todo: .Find()
// Todo: .FindFirstOf()
// Todo: .FindLastOf()
// Todo: .FindNotFirstOf()
// Todo: .FindNotLastOf()
// Todo: .Insert()  --> char & String
# include "NSLsrcs/String.hpp"

// ?Maths namespace
# include "NSLsrcs/Maths.hpp"

// ?Include Vector3 & Vector4 (for mathematical usage)
# include "NSLsrcs/MathVectors.h"

// ?Equivalent to std::pair<T1, T2> (without use of std::make_pair(...))
# include "NSLsrcs/Pair.hpp"

#endif
