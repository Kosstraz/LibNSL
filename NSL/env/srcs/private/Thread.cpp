/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../Thread.hpp"

pthread_t	Thread_MainThreadID = pthread_self();
std::map<String, void*> Thread::async_send = std::map<String, void*>();
Mutex Thread::mutex_send = Mutex();

Thread::~Thread()
{
	// !A régler
	// Juste après d'avoir lancer le thread (avec ThreadWrapper), Thread::Send et Thread::Receive
	//pour savoir quand on peut désallouer la mémoire
	/*if (this->wrapperHelper)
	{
		delete this->wrapperHelper->args;
		delete wrapperHelper;
	}*/
	
}

void
Thread::TryStop()
{
	pthread_cancel(this->thread);
	pthread_join(this->thread, nullptr);
}
