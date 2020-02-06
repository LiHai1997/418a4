#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  for (int i = 0; i < 3; ++i)
  {
  	if (A.min_corner(i) <= B.min_corner(i) && B.min_corner(i) <= A.max_corner(i))
  	{
  		continue;
  	}else if (A.min_corner(i) <= B.max_corner(i) && B.max_corner(i) <= A.max_corner(i))
  	{
  		continue;
  	}else if (B.min_corner(i) <= A.min_corner(i) && A.min_corner(i) <= B.max_corner(i))
  	{
  		continue;
  	}else if (B.min_corner(i) <= A.max_corner(i) && A.max_corner(i) <= B.max_corner(i))
  	{
  		continue;
  	}else
  	{
  		return false;
  	}
  }
  return true;

  ////////////////////////////////////////////////////////////////////////////
}

