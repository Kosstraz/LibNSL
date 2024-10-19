#include "../Barrier.hpp"

std::map<String, Barrier>
ManagedBarrier::sync_barrier = std::map<String, Barrier>();

Mutex::Strict
ManagedBarrier::sync_mutex = Mutex::Strict();

void
ManagedBarrier::Create(const String& barrierID, const uint& count) noexcept
{
	this->sync_mutex.WRLock();
	this->sync_barrier.emplace(barrierID, Barrier(count));
	this->sync_mutex.Unlock();
}

void
ManagedBarrier::Create(const String& barrierID, uint&& count) noexcept
{
	this->sync_mutex.WRLock();
	this->sync_barrier.emplace(barrierID, Barrier(Meta::Move(count)));
	this->sync_mutex.Unlock();
}

void
ManagedBarrier::Wait(const String& barrierID)
{
	this->sync_mutex.RLock();
	try
	{
		Barrier& b = this->sync_barrier.at(barrierID);
		this->sync_mutex.Unlock();
		b.Wait();
	}
	catch (...)
	{
		this->sync_mutex.Unlock();
		throw (ManagedBarrier::DoesNotExist());
	}
}

void
ManagedBarrier::Destroy(const String& barrierID)
{
	this->sync_mutex.WRLock();
	try
	{
		this->sync_barrier.erase(barrierID);
		this->sync_mutex.Unlock();
	}
	catch (...)
	{
		this->sync_mutex.Unlock();
		throw (ManagedBarrier::DoesNotExist());
	}
}

uint
ManagedBarrier::GetNumberOfBarriers(const String& barrierID) const
{
	uint	ret;

	this->sync_mutex.RLock();
	try
	{
		ret = static_cast<uint>(this->sync_barrier.at(barrierID).GetNumberOfBarriers());
		this->sync_mutex.Unlock();
	}
	catch (...)
	{
		this->sync_mutex.Unlock();
		throw (ManagedBarrier::DoesNotExist());
	}
	return (ret);
}

const char*
ManagedBarrier::DoesNotExist::what() const noexcept
{
	return ("BarrierID specified does not exist!");
}
