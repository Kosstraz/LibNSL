/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_MUTEX_HPP
#define NSL_MUTEX_HPP

# define TO_SECONDS(n)	static_cast<Mutex::seconds_t>(n)
# define TO_MSECONDS(n)	static_cast<Mutex::mseconds_t>(n)
# define TO_NSECONDS(n)	static_cast<Mutex::nseconds_t>(n)

# define MUTEX_LOCKED	0
# define MUTEX_BUSY		EBUSY

# include <pthread.h>
# include <time.h>

// Allows you to protect your data in differents threads when you read or write them.
class Mutex
{
public:
	typedef unsigned int		seconds_t;
	typedef unsigned long		mseconds_t;
	typedef unsigned long long	nseconds_t;

public:
	Mutex()		noexcept;
	~Mutex()	noexcept;

	void	Destroy();
	int		TryLock();
	void	TimedLock(seconds_t n)	noexcept;
	void	TimedLock(mseconds_t n)	noexcept;
	void	TimedLock(nseconds_t n)	noexcept;
	void	Lock()		noexcept;
	void	Unlock()	noexcept;

	class Strict;

private:
		pthread_mutex_t		mutex;
};

// Like the Mutex class, but here you can choose between ReadOnly locking or/and WriteRead locking.
class Mutex::Strict
{
public:
	Strict()	noexcept;
	~Strict()	noexcept;

	void	Destroy();
	int		TryRLock();
	void	TimedRLock(seconds_t n)	noexcept;
	void	TimedRLock(mseconds_t n)	noexcept;
	void	TimedRLock(nseconds_t n)	noexcept;
	void	RLock()		noexcept;

	int		TryWRLock();
	void	TimedWRLock(seconds_t n)	noexcept;
	void	TimedWRLock(mseconds_t n)	noexcept;
	void	TimedWRLock(nseconds_t n)	noexcept;
	void	WRLock()		noexcept;

	void	Unlock()	noexcept;

private:
	pthread_rwlock_t	mutex;
};

#endif
