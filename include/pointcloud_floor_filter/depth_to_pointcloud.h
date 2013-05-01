/*********************************************************************
 *
 *  Copyright (c) 2013, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.

 *  Author: Julius Kammerl (jkammerl@willowgarage.com)
 *
 */

#ifndef DEPTH_TO_POINTCLOUD_H_
#define DEPTH_TO_POINTCLOUD_H_

#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>

#include <vector>
#include <assert.h>


namespace floor_filtered_pointcloud
{

class DepthToPointCloud
{
public:
  DepthToPointCloud();
  virtual ~DepthToPointCloud();

  void initialize(const sensor_msgs::ImageConstPtr& depth_msg,
                  sensor_msgs::CameraInfoConstPtr& camera_info_msg);

  template<typename Point2D_T, typename Point3D_T>
    void depthTo3DPoint(Point2D_T& image_pos, float depth, Point3D_T& point)
  {
    assert(image_pos.x<projection_map_x_.size());
    assert(image_pos.y<projection_map_y_.size());

    point.x = projection_map_x_[(unsigned int)image_pos.x] * depth;
    point.y = projection_map_y_[(unsigned int)image_pos.y] * depth;
    point.z = depth;
  }


protected:
  // projection matrix
  std::vector<float> projection_map_x_;
  std::vector<float> projection_map_y_;
};

}

#endif /* DEPTH_TO_POINTCLOUD_H_ */