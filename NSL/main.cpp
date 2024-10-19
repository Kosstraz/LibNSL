#include "env/nsl.h"

	// THREADING EXEMPLE

float	ThreadTesting(String parameter /* can put infinite parameters */)
{
	bool	check;

	/* ... */
	parameter.Join("EZ");
	std::cout << "parameter: " << parameter << std::endl;
	Channel::Send("randomized", parameter);
	/* ... */
	check = Channel::Receive<bool>("goodSendingOK?");
	std::cout << "check: " << check << std::endl;
	/* ... */
	Thread::Return(42.42f);
	return (42.42f);
}

int	main(void)
{
	MultiThreading::Create("test1", ThreadTesting, String("norage"));
	std::cout << "MT IsAlive ? " << (MultiThreading::IsAlive("test1") ? "yes" : "no") << std::endl;
	std::cout << "MT IsExist ? " << (MultiThreading::IsExist("test1") ? "yes" : "no") << std::endl;
	Channel::Send("goodSendingOK?", true);
	MultiThreading::Wait("test1");
	std::cout << "MT IsAlive ? " << (MultiThreading::IsAlive("test1") ? "yes" : "no") << std::endl;
	std::cout << "MT IsExist ? " << (MultiThreading::IsExist("test1") ? "yes" : "no") << std::endl;

	std::cout << "\n\n------------------\n\n";

	Thread	myThread(ThreadTesting, "Bonjour, je suis Jean Guy ;) !!!");
	String	checkIfAllGood = Channel::Receive<String>("randomized");
	std::cout << "Received !\n";
	if (checkIfAllGood.Data() != nullptr)
		Channel::Send("goodSendingOK?", true);
	else
		Channel::Send("goodSendingOK?", false);
	std::cout << "Thread is alive ? " << (myThread.IsAlive() ? "yes" : "no") << std::endl;
	float retValue = myThread.Get<float>();
	std::cout << "retValue: " << retValue << std::endl;
	std::cout << "Thread is alive ? " << (myThread.IsAlive() ? "yes" : "no") << std::endl;/**/
	return (0);
}
