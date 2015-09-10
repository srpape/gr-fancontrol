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


#ifndef INCLUDED_FANCONTROL_FANBASEBAND_H
#define INCLUDED_FANCONTROL_FANBASEBAND_H

#include <fancontrol/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace fancontrol {

    /*!
     * \brief <+description of block+>
     * \ingroup fancontrol
     *
     */
    class FANCONTROL_API FanBaseBand : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<FanBaseBand> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of fancontrol::FanBaseBand.
       *
       * To avoid accidental use of raw pointers, fancontrol::FanBaseBand's
       * constructor is in a private implementation
       * class. fancontrol::FanBaseBand::make is the public interface for
       * creating new instances.
       */
      static sptr make(double samp_rate, bool run, int channel, int light, int fan);
    };

  } // namespace fancontrol
} // namespace gr

#endif /* INCLUDED_FANCONTROL_FANBASEBAND_H */

