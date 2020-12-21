#include "winbgi2.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void init(double *x, double *y,int N, int r)  //poczatkowe polozenie ludzi
{
	srand(time(NULL));
	double min = 100+r;
	double max = 700-r;
	int L = max - min + 1;
	for (int i = 0; i < N; i++)
	{
		x[i] = rand() % L + min;
		y[i] = rand() % L + min;
	}
}
void display(double *x, double *y, double *vx, double *vy, int N, int r)
{
	for (int i = 0; i < N; i++)
	{
		if (x[i] >= (700-r) && (y[i] > 380 && y[i] < 420))
		{
			x[i] = 1000;
			y[i] = 1000;
			vx[i] = 0;
			vy[i] = 0;
		}
		else
		{
			circle(x[i], y[i], r);
		}
	}
}
void predkosc(double *x, double *y, double *vx, double *vy,int N)
{
	double tgalfa,alfa;
	for (int i = 0; i < N; i++)
	{
		tgalfa = (400 - y[i]) / (690 - x[i]);
		alfa = atan(tgalfa);
		vx[i] = cos(alfa);
		vy[i] = sin(alfa);
	}
}
void run(double *x, double *y, double *vx, double *vy, int N, int r)
{
	for (int i = 0; i < N; i++)
	{
		x[i] += vx[i];
		y[i] += vy[i];
		if (x[i] >= (700-r)) { vx[i] = -vx[i]; }
		if(x[i]<=(100+r)) { vx[i] = -vx[i]; }
		if(y[i]<=(100+r)){ vy[i] = -vy[i]; }
		if(y[i]>=(700-r)){ vy[i] = -vy[i]; }
		
	}

}
void pokoj()
{
	line(100, 100, 700, 100);
	line(100, 100, 100, 700);
	line(100, 700, 700, 700);
	line(700, 700, 700, 420);
	line(700, 100, 700, 380);
}
void kolizja(double *x, double *y,double *vx, double *vy, int N)
{
	double v1x, v1y, nx, ny, vnx, vny, v2x, v2y,L;
	for (int i = 0; i < N; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			if (sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j])) <= N)
			{
				v1x = vx[i] - vx[j];
				v1y = vy[i] - vy[j];
				L = sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
				nx = (x[i] - x[j]) / L;
				ny = (y[i] - y[j]) / L;
				vnx = (v1x*nx + v1y*ny)*nx;
				vny = (v1x*nx + v1y*ny)*ny;
				v1x = v1x - vnx;
				v1y = v1y - vny;
				v2x = vnx;
				v2y = vny;
				vx[i] = vx[j] + v1x;
				vy[i] = vy[j] + v1y;
				vx[j] = vx[j] + v2x;
				vy[j] = vy[j] + v2x;

			}
		}
		
	}
	
				

}
void main()
{
	int N, r;
	printf("Podaj ilosc osob w pomieszczeniu:\n");
	scanf_s("%d", &N);
	printf("Podaj promien:\n");
	scanf_s("%d", &r);

	graphics(800, 800);			
	double *x, *y, *vx, *vy;
	x = (double*)malloc(N * sizeof(double));
	y = (double*)malloc(N * sizeof(double));
	vx = (double*)malloc(N * sizeof(double));
	vy = (double*)malloc(N * sizeof(double));
	///double x[20], y[20];
	//double vx[20], vy[20];
	init(x, y,N,r);
	display(x, y,vx,vy,N,r);
	predkosc(x, y, vx, vy,N);
	int k = 0;
	
	while(animate(50))
	{
		cleardevice();
		display(x, y,vx,vy,N,r);
		run(x, y, vx, vy,N,r);
		kolizja(x, y,vx,vy,N);
		
		if (k%10==0) { predkosc(x, y, vx, vy, N); }
		pokoj();
		k++;
	}
	wait();
}