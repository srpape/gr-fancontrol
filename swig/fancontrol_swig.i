/* -*- c++ -*- */

#define FANCONTROL_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "fancontrol_swig_doc.i"

%{
#include "fancontrol/FanBaseBand.h"
%}


%include "fancontrol/FanBaseBand.h"
GR_SWIG_BLOCK_MAGIC2(fancontrol, FanBaseBand);
