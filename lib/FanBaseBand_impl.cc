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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "FanBaseBand_impl.h"

namespace gr {
  namespace fancontrol {

    FanBaseBand::sptr
    FanBaseBand::make(double samp_rate, bool run, int channel, int light, int fan)
    {
      return gnuradio::get_initial_sptr
        (new FanBaseBand_impl(samp_rate, run, channel, light, fan));
    }

    /*
     * The private constructor
     */
    FanBaseBand_impl::FanBaseBand_impl(double samp_rate, bool run, int channel, int light, int fan)
      : gr::sync_block("FanBaseBand",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
        this->samp_rate = samp_rate;
        this->time_unit = samp_rate * 0.0003;
        this->message_index = 0;
        this->current_sample_index = 0;

        // Calculate the payload based on our input settings
        FanPacket p;
        switch (fan) {
        case 0:
            p.setFan(FAN_LOW);
            break;
        case 1:
            p.setFan(FAN_MED);
            break;
        case 2:
            p.setFan(FAN_HIGH);
            break;
        default:
            p.setFan(FAN_OFF);
            break;
       }

        p.setLight(light);
        p.setDipSwitches(channel);
        packet = p.getPacket();
    }

    /*
     * Our virtual destructor.
     */
    FanBaseBand_impl::~FanBaseBand_impl()
    {
    }

    int
    FanBaseBand_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        float *out = (float *) output_items[0];

        for (int i = 0; i < noutput_items; i++) {

            // This gives us a delay between sending packets
            if (message_index == packet.size()) {
                out[i] = 0;
                if (current_sample_index >= (time_unit * 2 *  packet.size())) {
                    message_index = 0;
                    current_sample_index = 0;
                } else {
                    current_sample_index++;
                    continue;
                }
            }

            if (packet[message_index]) {
                // We're sending a 1

                if (current_sample_index < time_unit) {
                    // At the start of the first time unit, we're on
                    out[i] = 1;
                } else if (current_sample_index > (time_unit * 3)) {
                    // At the end of the fourth time unit, move along the message index
                    ++message_index;
                    current_sample_index = 0;
                } else if (current_sample_index > (time_unit * 2)) {
                    // At the start of the third time unit, we're off
                    out[i] = 0;
                } else if (current_sample_index > (time_unit)) {
                    // At the start of the second time unit, we're still on
                    out[i] = 1;
                }

            } else {
                // We're sending a 0

                if (current_sample_index < time_unit) {
                    // At the start of the first time unit, we're off
                    out[i] = 0;
                } else if (current_sample_index > (time_unit * 3)) {
                    // At the end of the fourth time unit, move along the message index
                    ++message_index;
                    current_sample_index = 0;
                } else if (current_sample_index > (time_unit * 2)) {
                    // At the start of the third time unit, we're off
                    out[i] = 0;
                } else if (current_sample_index > (time_unit)) {
                    // At the start of the second time unit, we're still on
                    out[i] = 1;
                }

            }

            ++current_sample_index;
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace fancontrol */
} /* namespace gr */

