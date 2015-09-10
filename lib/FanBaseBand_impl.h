/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_FANCONTROL_FANBASEBAND_IMPL_H
#define INCLUDED_FANCONTROL_FANBASEBAND_IMPL_H

#include <fancontrol/FanBaseBand.h>

#include "FanPacket.hh"

namespace gr {
  namespace fancontrol {

    class FanBaseBand_impl : public FanBaseBand
    {
     private:
      double samp_rate;
      int current_sample_index;
      int message_index;
      int time_unit;
      std::vector<bool> packet;

     public:
      FanBaseBand_impl(double samp_rate, bool run, int channel, int light, int fan);
      ~FanBaseBand_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace fancontrol
} // namespace gr

#endif /* INCLUDED_FANCONTROL_FANBASEBAND_IMPL_H */

