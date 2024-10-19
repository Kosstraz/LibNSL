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

// ?Memory
# include "srcs/Allocator.hpp"

// ?Types capabilities
# include "srcs/TypesCap.hpp"

// ?Types capabilities
# include "srcs/TypesName.hpp"

// ?Types capabilities
# include "srcs/IsSubclassOf.hpp"

// ?Types capabilities
# include "srcs/IsConvertible.hpp"

// ?Constitutes a sort of heap of objects, of variable types, allocated
// Todo: Reforge all (and optimize)
# include "srcs/Pool.hpp"

// ?An in/out class
// Todo: optimize (a lot)
# include "srcs/IOStreams.hpp"

// ?Allows heavy mathematical calculations to be performed during compilation
# include "srcs/CompilationMaths.hpp"

// ?Utility
# include "srcs/SmartPtr.hpp"

// ?Utility
# include "srcs/Function.hpp"

// ?Utility
# include "srcs/Package.hpp"

// ?Utility
# include "srcs/Unpack.hpp"

// ?Utility
# include "srcs/Meta.hpp"

// ?A well threading system
# include "srcs/Thread.hpp"

// ?For threading & multithreading
# include "srcs/Channel.hpp"

// ?For multithreading
# include "srcs/Barrier.hpp"

// ?For threading and multithreading
# include "srcs/Async.hpp"

// ?For threading & multithreading
# include "srcs/Mutex.hpp"

// ?Allows secure multithreading and easy access to threads via their identifier ID
# include "srcs/MultiThreading.hpp"

// ?Equivalent à std::string (en beaucoup + performant & avec + de fonctionnalités)
// Todo: .Find()
// Todo: .FindFirstOf()
// Todo: .FindLastOf()
// Todo: .FindNotFirstOf()
// Todo: .FindNotLastOf()
// Todo: .Insert()  --> char & String
# include "srcs/String.hpp"

// ?Maths namespace
# include "srcs/Maths.hpp"

// ?Include Vector3 & Vector4 (for mathematical usage)
# include "srcs/MathVectors.h"

// ?Equivalent to std::pair<T1, T2> (without use of std::make_pair(...))
# include "srcs/Pair.hpp"

#endif
