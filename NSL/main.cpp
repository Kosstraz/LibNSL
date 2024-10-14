#include "env/nsl.h"

/*int	main()
{
	//for (int i = 0 ; i < 10 ; i++)
	//	Benchmark_Vector3_AVX();
	//_mm_ez /= 10;
	//std::cout << "\e[1m\n\nAverage perf --> " << _mm_ez << "%\e[0m" << std::endl;
	return (0);
}*/

	// THREADING TESTING

float	ThreadTesting(String parameter /* can put infinite parameters */)
{
	bool	check;

	/* ... */
	parameter.Join("EZ");
	std::cout << "parameter: " << parameter << std::endl;
	Thread::Send("randomized", parameter);
	/* ... */
	check = Thread::Receive<bool>("goodSendingOK?");
	std::cout << "check: " << check << std::endl;
	/* ... */
	Thread::Return(42.42f);
	return (42.42f);
}

int	main(void)
{
	Thread	myThread(ThreadTesting, "Bonjour, je suis Jean Guy ;) !!!");
	String	checkIfAllGood = myThread.Receive<String>("randomized");
	std::cout << "Received !\n";
	if (checkIfAllGood.Data() != nullptr)
		Thread::Send("goodSendingOK?", true);
	else
		Thread::Send("goodSendingOK?", false);
	float retValue = myThread.Get<float>();
	std::cout << "retValue: " << retValue << std::endl;
	return (0);
}
