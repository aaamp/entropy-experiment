#ifndef ENTROPY_H_
#define ENTROPY_H_

#include <vector>
#include <thread>
#include "vec2.h"
#include "particle.h"


using namespace std;
class entropy
{
public:
 entropy(float p_grid, float v_grid, int p_count, int v_count, float r, float v);

 const void ClearBoxes();
 const void LoadParticles(vector<particle>p);
 const void GroupParticles();
 const double& calcProbability();
 const double& calcEntropy();
 const vector<vector< vector<vector<int>>>>& GetBoxes();
private:
 vector<particle> particles;
 vector<vector< vector<vector<int>>>>boxes;
 float velocity_box_size;
 int velocity_box_count;
 float position_box_size;
 int position_box_count;
 float position_limit;
 float velocity_limit;
};


#endif