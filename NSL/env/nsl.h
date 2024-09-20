/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NEW_STANDARD_LIBRARY_H
#define NEW_STANDARD_LIBRARY_H

# ifndef FORCEINLINE
#  define FORCEINLINE __attribute__((always_inline))
# endif

# ifndef MALLOC_ATTR
#  define MALLOC_ATTR __attribute__((malloc))
# endif

// !Two memory leaks in threading edge case (in the Thread class)
// !If not, no memory leak currently detected

// ?Similaire à std::allocator
# include "srcs/Allocator.hpp"

// ?A smart pointer, similar to std::shared_ptr<T>
# include "srcs/SmartPtr.hpp"

// ?Type capabilities (everything is calculated at compile time)
// Upcoming additions
# include "srcs/TypesCap.hpp"

// ?Equivalent à std::is_base_of_v
# include "srcs/IsSubclassOf.hpp"

// ?Similaire à std::is_convertible_v
# include "srcs/IsConvertible.hpp"

// ?Constitutes a sort of heap of objects, of variable types, allocated
// To optimize
# include "srcs/Pool.hpp"

// ?Equivalent à std::cout/cin (version nulle)
// To optimize (a lot)
# include "srcs/IOStreams.hpp"

// ?Allows heavy mathematical calculations to be performed during compilation
# include "srcs/CompilationMaths.hpp"

// ?Equivalent à std::function
# include "srcs/Function.hpp"

// ?Packing a variadic argument | équivalent to std::tuple
# include "srcs/Package.hpp"

// ?Allows you to unpack a Package<...> and apply it to a given function
# include "srcs/Unpack.hpp"

// ?Equivalent à std::thread
// INFO:
// Please exit threads cleanly with Thread::Return(...), particularly if you need a return value
// You can send information between threads or to the parent thread (Thread::Send() & .Receive<>()).
# include "srcs/Thread.hpp"

// ?Equivalent à std::mutex (avec + de fonctionnalités)
# include "srcs/Mutex.hpp"

// ?Enables secure multithreading and easy access to threads via their identifier
# include "srcs/MultiThreading.hpp"

// ?Some utilities
# include "srcs/Memory.hpp"

// ?Equivalent à std::string (en beaucoup + performant & avec + de fonctionnalités)
// Todo: .Find()
// Todo: .FindFirstOf()
// Todo: .FindLastOf()
// Todo: .FindNotFirstOf()
// Todo: .FindNotLastOf()
// Todo: .Insert()  --> char & String
# include "srcs/String.hpp"

#endif
