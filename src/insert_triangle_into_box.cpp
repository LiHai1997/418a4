#include "insert_triangle_into_box.h"
#include <iostream>

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  float min_x,min_y,min_z,max_x,max_y,max_z;

  if (a(0) < b(0) && a(0) < c(0))
  {
  	min_x = a(0);
  }else if (b(0) < c(0))
  {
  	min_x = b(0);
  }else
  {
  	min_x = c(0);
  }

  if (a(1) < b(1) && a(1) < c(1))
  {
  	min_y = a(1);
  }else if (b(1) < c(1))
  {
  	min_y = b(1);
  }else
  {
  	min_y = c(1);
  }

  if (a(2) < b(2) && a(2) < c(2))
  {
  	min_z = a(2);
  }else if (b(2) < c(2))
  {
  	min_z = b(2);
  }else
  {
  	min_z = c(2);
  }

  if (a(0) > b(0) && a(0) > c(0))
  {
  	max_x = a(0);
  }else if (b(0) > c(0))
  {
  	max_x = b(0);
  }else
  {
  	max_x = c(0);
  }

  if (a(1) > b(1) && a(1) > c(1))
  {
  	max_y = a(1);
  }else if (b(1) > c(1))
  {
  	max_y = b(1);
  }else
  {
  	max_y = c(1);
  }

  if (a(2) > b(2) && a(2) > c(2))
  {
  	max_z = a(2);
  }else if (b(2) > c(2))
  {
  	max_z = b(2);
  }else
  {
  	max_z = c(2);
  }


  if (B.min_corner(0) >= min_x)
  {
  	B.min_corner(0) = min_x;
  }

  if (B.min_corner(1) >= min_y)
  {
  	B.min_corner(1) = min_y;
  }

  if (B.min_corner(2) >= min_z)
  {
  	B.min_corner(2) = min_z;
  }

  if (B.max_corner(0) <= max_x)
  {
  	B.max_corner(0) = max_x;
  }

  if (B.max_corner(1) <= max_y)
  {
  	B.max_corner(1) = max_y;
  }

  if (B.max_corner(2) <= max_z)
  {
  	B.max_corner(2) = max_z;
  }

  ////////////////////////////////////////////////////////////////////////////
}


