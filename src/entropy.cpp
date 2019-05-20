#include "symul.h"
#include <iostream>
#include <thread>
#include <algorithm>
#include <cmath>
#include <vector>
#include "particle.h"
#include "entropy.h"

using namespace std;
entropy::entropy(float p_grid, float v_grid, int p_count, int v_count, float r, float v)
{
	position_box_size = p_grid;
	velocity_box_size = v_grid;
	position_box_count = p_count;
	velocity_box_count = v_count;
	position_limit = r;
	velocity_limit = v;
	vector<vector< vector<vector<int>>>>a(p_count, vector<vector<vector<int>>>(p_count, vector<vector<int>>(v_count, vector<int>(v_count))));
	boxes = a;
}

const void entropy::GroupParticles()
{
	int pmax = position_box_count - 1;
	int vmax = velocity_box_count - 1;
	for (int i = 0; i < particles.size(); i++)
	{
		vec2f position = particles[i].getPosition();
		float px = position.getX() + position_limit;
		float py = position.getY() + position_limit;

		vec2f velocity = particles[i].getVelocity();
		float vx = velocity.getX() + velocity_limit;
		float vy = velocity.getY() + velocity_limit;

		int ipx = px / position_box_size;
		int ipy = py / position_box_size;
		int ivx = px / position_box_size;
		int ivy = py / position_box_size;
		boxes[min(ipx, pmax)][min(ipy, pmax)][min(ivx, vmax)][min(ivy, vmax)]++;
	}
}

const void entropy::ClearBoxes()
{
	for (int i = 0; i < position_box_count; i++)
	{
		for (int j = 0; j < position_box_count; i++)
		{
			for (int k = 0; k < velocity_box_count; k++)
			{
				for (int l = 0; l < velocity_box_count; l++)
				{
					boxes[i][j][k][l] = 0;
				}
			}
		}
	}
}
const void entropy::LoadParticles(vector<particle>p)
{
	particles = p;
}
const double& entropy::calcProbability()
{
	double res = pow(exp(1), calcEntropy());
	return res;
}

const double & entropy::calcEntropy()
{
	int n = particles.size();
	int ns = 0;
	double res = n * log(n);
	for (int i = 0; i < position_box_count; i++)
	{
		for (int j = 0; j < position_box_count; j++)
		{
			for (int k = 0; k < velocity_box_count; k++)
			{
				for (int l = 0; l < velocity_box_count; l++)
				{
					ns = boxes[i][j][k][l];
					if (ns > 0)
					{
						res -= ns * log(ns);
					}
				}
			}
		}
	}
	return res;
}

const vector<vector<vector<vector<int>>>>& entropy::GetBoxes()
{
	return boxes;
}

