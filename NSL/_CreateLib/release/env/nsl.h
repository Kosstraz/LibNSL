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
# include "NSLsrcs/Allocator.hpp"

// ?Types capabilities
# include "NSLsrcs/TypesCap.hpp"

// ?Types capabilities
# include "NSLsrcs/TypesName.hpp"

// ?Types capabilities
# include "NSLsrcs/IsSubclassOf.hpp"

// ?Types capabilities
# include "NSLsrcs/IsConvertible.hpp"

// ?Constitutes a sort of heap of objects, of variable types, allocated
// Todo: Reforge all (and optimize)
# include "NSLsrcs/Pool.hpp"

// ?An in/out class
// Todo: optimize (a lot)
# include "NSLsrcs/IOStreams.hpp"

// ?Allows heavy mathematical calculations to be performed during compilation
# include "NSLsrcs/CompilationMaths.hpp"

// ?Utility
# include "NSLsrcs/SmartPtr.hpp"

// ?Utility
# include "NSLsrcs/Function.hpp"

// ?Utility
# include "NSLsrcs/Package.hpp"

// ?Utility
# include "NSLsrcs/Unpack.hpp"

// ?Utility (the file and namespace name will be changed)
# include "NSLsrcs/Meta.hpp"

// ?A well threading system
# include "NSLsrcs/Thread.hpp"

// ?For threading & multithreading
# include "NSLsrcs/Channel.hpp"

// ?For multithreading
# include "NSLsrcs/Barrier.hpp"

// ?For threading and multithreading
# include "NSLsrcs/Async.hpp"

// ?For threading & multithreading
# include "NSLsrcs/Mutex.hpp"

// ?Allows secure multithreading and easy access to threads via their identifier ID
# include "NSLsrcs/MultiThreading.hpp"

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
