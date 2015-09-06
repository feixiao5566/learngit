/*
 * openRatSLAM
 *
 * utils - General purpose utility helper functions mainly for angles and readings settings
 *
 * Copyright (C) 2012
 * David Ball (david.ball@qut.edu.au) (1), Scott Heath (scott.heath@uqconnect.edu.au) (2)
 *
 * RatSLAM algorithm by:
 * Michael Milford (1) and Gordon Wyeth (1) ([michael.milford, gordon.wyeth]@qut.edu.au)
 *
 * 1. Queensland University of Technology, Australia
 * 2. The University of Queensland, Australia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "local_view_match.h"
#include "../utils/utils.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
using namespace std;
#include <boost/foreach.hpp>
#include <algorithm>

#include <stdio.h>

namespace ratslam
{



LocalViewMatch::LocalViewMatch(ptree settings)
{
  get_setting_from_ptree(VT_MIN_PATCH_NORMALISATION_STD, settings, "vt_min_patch_normalisation_std", (double)0);
  get_setting_from_ptree(VT_PATCH_NORMALISATION, settings, "vt_patch_normalise", 0);
  get_setting_from_ptree(VT_NORMALISATION, settings, "vt_normalisation", (double) 0);
  get_setting_from_ptree(VT_SHIFT_MATCH, settings, "vt_shift_match", 25);
  get_setting_from_ptree(VT_STEP_MATCH, settings, "vt_step_match", 5);
  get_setting_from_ptree(VT_PANORAMIC, settings, "vt_panoramic", 0);
 
  get_setting_from_ptree(VT_MATCH_THRESHOLD, settings, "vt_match_threshold", 0.00);
  get_setting_from_ptree(TEMPLATE_X_SIZE, settings, "template_x_size", 1);
  get_setting_from_ptree(TEMPLATE_Y_SIZE, settings, "template_y_size", 1);
  get_setting_from_ptree(IMAGE_VT_X_RANGE_MIN, settings, "image_crop_x_min", 0);
  get_setting_from_ptree(IMAGE_VT_X_RANGE_MAX, settings, "image_crop_x_max", -1);
  get_setting_from_ptree(IMAGE_VT_Y_RANGE_MIN, settings, "image_crop_y_min", 0);
  get_setting_from_ptree(IMAGE_VT_Y_RANGE_MAX, settings, "image_crop_y_max", -1);

  TEMPLATE_SIZE = 24;//TEMPLATE_X_SIZE * TEMPLATE_Y_SIZE;

  templates.reserve(10000);

  current_view.resize(TEMPLATE_SIZE);
  

  current_vt = 0;
  prev_vt = 0;
}


LocalViewMatch::~LocalViewMatch()
{

}

void LocalViewMatch::on_image(const unsigned char *view_rgb)
{
  if (view_rgb == NULL)
    return;

  this->view_rgb = view_rgb;
  cout<<view_rgb<<endl;

  convert_view_to_view_template(true);
  prev_vt = get_current_vt();
  unsigned int vt_match_id;
  compare(vt_error, vt_match_id);//均差和匹配id
  if (vt_error <= VT_MATCH_THRESHOLD)//我这里的VT_MATCH_THRESHOLD值必须是0
  {//当前id和模板某个id匹配
    set_current_vt((int)vt_match_id);//检查这个匹配模板
    cout << "VTM[" << setw(4) << get_current_vt() << "] " << endl;
    cout.flush();
  }
  else
  {
    vt_relative_rad = 0;
    set_current_vt(create_template());//检测这个创建的模板值
    cout << "VTN[" << setw(4) << get_current_vt() << "] " << endl;
    cout.flush();
  }

}
void LocalViewMatch::convert_view_to_view_template(bool grayscale)
{
  int counter = 0;
  //先把current清空
//  current_view.erase(current_view.begin());
//  vector<double>(current_view).swap(current_view);
  current_view.clear();
  vector<double>(current_view).swap(current_view);
  for (int pos = 0; pos < 24; pos++)//24
  {
//    cout<<view_rgb[pos];
    current_view.push_back(view_rgb[pos]);
    cout<<"convert_view_template";
    cout<<current_view[pos]<<endl;
  }
  size_t i=0;
  cout<<"myconvert"<<endl;
  for(vector<double>::iterator iter = current_view.begin();iter != current_view.end(); ++iter, ++i )
  {  
    cout<<*iter;
    counter++;
  }
  
//  current_view.push_back((double)view_rgb);
  cout <<"convertend"<<counter<< endl;
}

// create and add a visual template to the collection
int LocalViewMatch::create_template()
{
  templates.resize(templates.size() + 1);
  VisualTemplate * new_template = &(*(templates.end() - 1));

  new_template->id = templates.size() - 1;
  double * data_ptr = &current_view[0];//可以加入epc标签
  new_template->data.reserve(TEMPLATE_SIZE);
  for (int i = 0; i < TEMPLATE_SIZE; i++)
  {
    printf("create_template data_ptr%d\n", *(view_rgb));
    new_template->data.push_back(*(view_rgb++));
  }
  return templates.size() - 1;
}

// compare a visual template to all the stored templates, allowing for 
// slen pixel shifts in each direction
// returns the matching template and the MSE
void LocalViewMatch::compare(double &vt_err, unsigned int &vt_match_id)
{
  if (templates.size() == 0)
  {
    vt_err = DBL_MAX;
    vt_error = vt_err;
    return;
  }

  vector<double>::iterator iter = current_view.begin();
  double *data = &current_view[0];
  printf("\nlook this\n");
   size_t i=0;
    for(vector<double>::iterator iter = current_view.begin();iter != current_view.end(); ++iter, ++i )
  {  
    cout<<*iter;
  }
  printf("\nlook this\n");
  double mindiff, cdiff;
  mindiff = DBL_MAX;

  vt_err = DBL_MAX;
  int min_template = 0;

  double *template_ptr;
  double *column_ptr;
  double *template_row_ptr;
  double *column_row_ptr;
  double *template_start_ptr;
  double *column_start_ptr;
  int row_size;
  int sub_row_size;
  double *column_end_ptr;
  VisualTemplate vt;
  int min_offset;

  int offset;
  double epsilon = 0.005;

printf("\n");
// Magic. Do not touch.
// i use vt_error to a flag, 0-----> found    1-----> not found
	BOOST_FOREACH(vt, templates)
	{
	  int ii = 0;
    if(vt.data[ii] == data[ii])
    {
      for(int i = 0; i<24; i++)
      {
        if(vt.data[ii+i] == data[ii+i])
        {
          if(23 == i)
          {
            vt_error = 0;
            vt_match_id = vt.id;
            return;
          }
        }
        else
        {
          break;
        }
      }
      
    }
    vt_error = 1;
    vt_match_id = 0;
	}//end of BOOST_FOREACH
}

}
