#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Fanbaseband
# Generated: Wed Sep  9 20:11:38 2015
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import fancontrol
import osmosdr
import time
import argparse

class FanBaseband(gr.top_block):

    def __init__(self, args):
        gr.top_block.__init__(self)


    	self._channel = args.channel
        self._light = args.light
        self._fan = args.fan 

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 8000000
        self.center_freq = center_freq = 303747000

        ##################################################
        # Blocks
        ##################################################
        self.osmosdr_sink_0 = osmosdr.sink( args="numchan=" + str(1) + " " + "" )
        self.osmosdr_sink_0.set_sample_rate(samp_rate)
        self.osmosdr_sink_0.set_center_freq(center_freq, 0)
        self.osmosdr_sink_0.set_freq_corr(0, 0)
        self.osmosdr_sink_0.set_gain(14, 0)
        self.osmosdr_sink_0.set_if_gain(40, 0)
        self.osmosdr_sink_0.set_bb_gain(20, 0)
        self.osmosdr_sink_0.set_antenna("1", 0)
        self.osmosdr_sink_0.set_bandwidth(2e6, 0)
          
        self.fancontrol_FanBaseBand_0 = fancontrol.FanBaseBand(samp_rate, True, self._channel, self._light, self._fan)
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.fancontrol_FanBaseBand_0, 0), (self.blocks_float_to_complex_0, 0))
        self.connect((self.fancontrol_FanBaseBand_0, 0), (self.blocks_float_to_complex_0, 1))
        self.connect((self.blocks_float_to_complex_0, 0), (self.osmosdr_sink_0, 0))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.osmosdr_sink_0.set_sample_rate(self.samp_rate)

    def get_center_freq(self):
        return self.center_freq

    def set_center_freq(self, center_freq):
        self.center_freq = center_freq
        self.osmosdr_sink_0.set_center_freq(self.center_freq, 0)

if __name__ == '__main__':
    import ctypes
    import sys
   
    parser = argparse.ArgumentParser(description='Control house fans') 
    parser.add_argument("-c", "--channel", type=int, help="The fan's channel (0-15)")
    parser.add_argument("-l", "--light", type=int, help="The fan's light level (0-63)")
    parser.add_argument("-f", "--fan", type=int, help="The fan's speed (0-3)")

    args = parser.parse_args();

    if args.channel is None:
      print("Missing channel")
      sys.exit(1)
   
    if args.light is None:
      print("Missing fan light level")
      sys.exit(1)

    if args.fan is None:
      print("Missing fan speed")
      sys.exit(1)

    tb = FanBaseband(args)
    tb.start()
    time.sleep(0.10) 
    tb.stop()
