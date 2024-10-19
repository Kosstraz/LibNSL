#ifndef NSL_ASYNC_HPP
#define NSL_ASYNC_HPP

# include "Thread.hpp"
# include <map>


// Allows to a thread to pause, and another to continue him
class Thread::Async final
{
public:
	Async()				= delete;
	Async(const Async&)	= delete;
	Async(Async&&)		= delete;
	~Async()			= delete;

	// The current thread will be in pause
	static void MakePause(const uint& id) noexcept;
	// The current thread will be in pause
	static void MakePause(uint&& id) noexcept;

	// Try to play the thread by the id
	static void TryPlay(const uint& id) noexcept;
	// Try to play the thread by the id
	static void TryPlay(uint&& id) noexcept;

	// Play the thread by the id
	static void Play(const uint& id) noexcept;
	// Play the thread by the id
	static void Play(uint&& id) noexcept;

private:
	static std::map<uint, bool>	async_pause;
	static Mutex				mutex;
};

#endif
