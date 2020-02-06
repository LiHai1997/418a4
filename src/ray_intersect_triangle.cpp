#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>
#include <limits.h>

bool plane_intersect(
  const Ray & ray, const double min_t, const double max_t, const Eigen::RowVector3d &plane_point, const Eigen::RowVector3d &plane_normal, double & t)
{
  
  Eigen::RowVector3d e = ray.origin, d = ray.direction;

    double tmp1 = (plane_point - e).dot(plane_normal);
    double tmp2 = d.dot(plane_normal);
    if (tmp2 >= 0 && tmp2 <= 1e-6){
        if (tmp1 >= 0 && tmp1 <= 1e-6){
            
            t = min_t;
            return true;
        }else 
            return false;
    }
    
    t = tmp1 / tmp2;
    if (t >= min_t && t <= max_t){
        return true;
    }
    return false;
}

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = std::numeric_limits<double>::infinity();

  Eigen::RowVector3d q = B-A;
  Eigen::RowVector3d p = C-A;
  Eigen::RowVector3d triangle_n = q.cross(p).normalized();

  double plane_t;

  if (plane_intersect(ray, min_t, max_t, A, triangle_n, plane_t))
  {
    Eigen::RowVector3d p0 = ray.origin + plane_t * ray.direction;
    Eigen::RowVector3d e0 = B-A;
    Eigen::RowVector3d e1 = C-B;
    Eigen::RowVector3d e2 = A-C;

    Eigen::RowVector3d x0 = p0 - A;
    Eigen::RowVector3d x1 = p0 - B;
    Eigen::RowVector3d x2 = p0 - C;
    if (triangle_n.dot(e0.cross(x0)) > 0 && triangle_n.dot(e1.cross(x1)) > 0 && triangle_n.dot(e2.cross(x2)) > 0)
    {
      t = plane_t;
      return true;
    }
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

