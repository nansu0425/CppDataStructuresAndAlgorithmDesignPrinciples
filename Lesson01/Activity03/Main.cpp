#include "Printer.h"

int main()
{
	Printer printer;

	printer.AddJob("Jun");
	printer.AddJob("MinJu", 2);
	printer.AddJob("Jin");
	printer.AddJob("Gang", 4);

	printer.ProcessJobs();

	return 0;
}