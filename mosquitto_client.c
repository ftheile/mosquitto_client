#include "client.h"
#include <mosquitto.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

static struct cli theClient;

#define MAX_SAMPLES 20

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("Usage:\n");
		printf("  %s <broker URL>\n", argv[0]);
		return -1;
	} else {
		int i;

		mosquitto_lib_init();
		cli_init(&theClient, argv[1]);

		// Generate simulated measurements and publish them:
		for (i=0; i<MAX_SAMPLES; i++) {
			float temp = 10 * sin(i * 2 * M_PI / MAX_SAMPLES);
			cli_publish(&theClient, temp);
			sleep(1);
		}

		cli_cleanup(&theClient);
		mosquitto_lib_cleanup();

		return 0;
	}
}
