#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <iostream>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = 0;

  double min_dist =  std::numeric_limits<double>::infinity();

  for (int i = 0; i < points.rows(); ++i)
  {
  	Eigen::RowVector3d point = points.row(i);
  	double cur_dist = (point-query).squaredNorm();
  	if (cur_dist < min_dist)
  	{
  		I=i;
  		min_dist = cur_dist;
  	}
  }
  sqrD = min_dist;
  ////////////////////////////////////////////////////////////////////////////
}
