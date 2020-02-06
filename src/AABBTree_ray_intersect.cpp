#include "AABBTree.h"
#include "MeshTriangle.h"
#include "CloudPoint.h"
#include <limits.h>
#include <ray_intersect_box.h>
#include <ray_intersect_triangle.h>
#include <iostream>


// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (ray_intersect_box(ray, this->box, min_t, max_t))
  {
    bool left_hit = false;
    bool right_hit = false;
    double left_t = std::numeric_limits<double>::infinity();
    double right_t = std::numeric_limits<double>::infinity();

    std::shared_ptr<Object> left_descendant;
    std::shared_ptr<Object> right_descendant;

    left_hit = this->left->ray_intersect(ray, min_t, max_t, left_t, left_descendant);
    right_hit = this->right->ray_intersect(ray, min_t, max_t, right_t, right_descendant);

    if (left_hit && right_hit)
    {
      if (left_t < right_t)
      {
        t = left_t;
        descendant = left_descendant;
      }else
      {
        t = right_t;
        descendant = right_descendant;
      }

    }else if (left_hit)
    {
      t = left_t;
      descendant = left_descendant;
    }else if (right_hit)
    {
      t = right_t;
      descendant = right_descendant;
    }else
    {
      return false;
    }
    std::shared_ptr<MeshTriangle> meshTriangle1, meshTriangle2;
    if (t == left_t && left_hit)
    {
      meshTriangle1 = std::dynamic_pointer_cast<MeshTriangle>(this->left);
      if (meshTriangle1)
      {
        descendant = this->left;
      }
    }
    if (t == right_t && right_hit)
    {
      meshTriangle2 = std::dynamic_pointer_cast<MeshTriangle>(this->right);
      if (meshTriangle2)
      {
        descendant = this->right;
      }
    }
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

