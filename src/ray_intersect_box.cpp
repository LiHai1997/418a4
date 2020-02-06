#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d inv_dir(1.0/ray.direction(0), 1.0/ray.direction(1), 1.0/ray.direction(2));

  float hit_t_min, hit_t_max, t_y_min, t_y_max, t_z_min, t_z_max;
  float min_x = box.min_corner(0);
  float min_y = box.min_corner(1);
  float min_z = box.min_corner(2);
  float max_x = box.max_corner(0);
  float max_y = box.max_corner(1);
  float max_z = box.max_corner(2);

  if (inv_dir(0) > 0)
  {
  	hit_t_min = (min_x - ray.origin(0)) * inv_dir(0);
  	hit_t_max = (max_x - ray.origin(0)) * inv_dir(0);
  }
  else
  {
  	hit_t_min = (max_x - ray.origin(0)) * inv_dir(0);
  	hit_t_max = (min_x - ray.origin(0)) * inv_dir(0);
  }

  if (inv_dir(1) > 0)
  {
  	t_y_min = (min_y - ray.origin(1)) * inv_dir(1);
  	t_y_max = (max_y - ray.origin(1)) * inv_dir(1);
  }
  else
  {
  	t_y_min = (max_y - ray.origin(1)) * inv_dir(1);
  	t_y_max = (min_y - ray.origin(1)) * inv_dir(1);
  }

  if (inv_dir(2) > 0)
  {
  	t_z_min = (min_z - ray.origin(2)) * inv_dir(2);
  	t_z_max = (max_z - ray.origin(2)) * inv_dir(2);
  }
  else
  {
  	t_z_min = (max_z - ray.origin(2)) * inv_dir(2);
  	t_z_max = (min_z - ray.origin(2)) * inv_dir(2);
  }

  if (hit_t_min > t_y_max || t_y_min > hit_t_max)
  {
  	return false;
  }

  if (t_y_min > hit_t_min)
  {
  	hit_t_min = t_y_min;
  }
  if (t_y_max < hit_t_max)
  {
  	hit_t_max = t_y_max;
  }


  if (hit_t_min > t_z_max || t_z_min > hit_t_max)
  {
  	return false;
  }

  if (t_z_min > hit_t_min)
  {
  	hit_t_min = t_z_min;
  }

  if (t_z_max < hit_t_max)
  {
  	hit_t_max = t_z_max;
  }

  if ((hit_t_min >= min_t && min_t <= max_t) || (hit_t_max >= min_t && min_t <= max_t))
  {
  	return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
