/*
 * scoreIt_main.cpp
 *
 *  Created on: Dec 23, 2009
 *      Author: canadi
 */

#include "docking/docking.h"

int main(int argc, char **argv)
{
	if (argc != 7 && argc != 8)
	{
		printf("usage: scoreit R beta1 gamma1 alpha2 beta2 gamma2 [configuration]\n");
		exit(1);
	}

	Configuration configuration;

	if (argc == 8)
	{
		configuration.init(argv[7]);
	}else
	{
		configuration.init("config.txt");
	}

	ScoreConfiguration scoreConfiguration;

	sscanf(argv[1], "%lf", &scoreConfiguration.R);
	sscanf(argv[2], "%lf", &scoreConfiguration.beta1);
	sscanf(argv[3], "%lf", &scoreConfiguration.gamma1);
	sscanf(argv[4], "%lf", &scoreConfiguration.alpha);
	sscanf(argv[5], "%lf", &scoreConfiguration.beta2);
	sscanf(argv[6], "%lf", &scoreConfiguration.gamma2);

	Docking justDoIt(configuration);

	printf("%.16lf\n", justDoIt.scoreIt(scoreConfiguration));

	return 0;
}
