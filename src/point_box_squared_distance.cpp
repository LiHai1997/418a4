#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  Eigen::RowVector3d closest;
  double query_axis, max, min;

  for (int i = 0; i < 3; ++i)
  {
  	query_axis = query(i);
  	max = box.max_corner(i);
  	min = box.min_corner(i);

  	if (query_axis > max)
  	{
  		closest(i) = max;
  	}
  	else if (query_axis < min)
  	{
  		closest(i) = min;
  	}
  	else
  	{
  		closest(i) = query_axis;
  	}
  }
  return (closest - query).squaredNorm();
  ////////////////////////////////////////////////////////////////////////////
}
