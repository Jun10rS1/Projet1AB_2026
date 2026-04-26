#include "vl53l5cx_api.h"
#include "counter.h"
#include "utils.h"

static int counter;

int moy(int col[])
{
	int m = 0;
	int n = sizeof(col);
	for(int i=0; i<n; i++)
	{
		m += col[i];
	}
	return m/n;
}


VL53L5CX_Configuration Dev;
VL53L5CX_ResultsData Results;
int distance[8][8];

void setup()
{
	uint8_t status = vl53l5cx_get_ranging_data(&Dev, &Results);

	if(status == VL53L5CX_STATUS_OK)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				distance[i][j] = Results.distance_mm[i*8 + j];
			}
		}
	}
}

void loop()
{
	counter = 0;
	update_counter(distance, counter);

    //int value = value_counter();
}
