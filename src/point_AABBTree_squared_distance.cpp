#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <bits/stdc++.h>
#include "point_box_squared_distance.h"
#include "Object.h"
#include "CloudPoint.h"
#include <limits.h>
#include <bits/stdc++.h>

typedef std::pair<double, std::shared_ptr<Object>> q_pair;
bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  std::priority_queue<q_pair, std::vector<q_pair>, std::greater<q_pair>> queue;
  double min_dist = std::numeric_limits<double>::infinity();
  double cur_dist = point_box_squared_distance(query, root->box);

  queue.push(std::make_pair(cur_dist, root));


  while(!queue.empty()){
    std::pair<double, std::shared_ptr<Object>> cur_pair = queue.top();
    double sub_dist = cur_pair.first;
    std::shared_ptr<Object> cur_node = cur_pair.second;
    queue.pop();

    if (sub_dist >= min_sqrd && sub_dist <= max_sqrd && sub_dist < min_dist)
    {
      std::shared_ptr<CloudPoint> cloudPoint = std::dynamic_pointer_cast<CloudPoint>(cur_node);
      if (cloudPoint)
      {
        if (cloudPoint->point_squared_distance(query, min_sqrd, max_sqrd, sub_dist, descendant))
        {
          if (sub_dist < min_dist)
          {
            min_dist = sub_dist;
            descendant = cloudPoint;
          }
        }
      }
      else
      {
        std::shared_ptr<AABBTree> treePoint = std::dynamic_pointer_cast<AABBTree>(cur_node);

        double left_dist = point_box_squared_distance(query, treePoint->left->box);
        queue.push(std::make_pair(left_dist, treePoint->left));

        double right_dist = point_box_squared_distance(query, treePoint->right->box);
        queue.push(std::make_pair(right_dist, treePoint->right));
      }
    }
  }
  sqrd = min_dist;
  if (min_dist >= min_sqrd && min_dist <= max_sqrd)
  {
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
