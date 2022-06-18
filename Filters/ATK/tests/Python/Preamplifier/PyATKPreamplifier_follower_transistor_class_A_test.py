#!/usr/bin/env python

from ATK.Core import DoubleInPointerFilter, DoubleOutPointerFilter
from ATK.Tools import DoubleOversampling6points5order_32Filter, DoubleOversampling6points5order_16Filter, DoubleOversampling6points5order_8Filter, DoubleOversampling6points5order_4Filter, DoubleDecimationFilter
from ATK.EQ import DoubleButterworthLowPassFilter
from ATK.Preamplifier import DoubleFollowerTransistorClassAFilter

def filter_32(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  overfilter = DoubleOversampling6points5order_32Filter()
  overfilter.set_input_sampling_rate(48000)
  overfilter.set_output_sampling_rate(48000 * 32)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleFollowerTransistorClassAFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(48000 * 32)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000 * 32)
  lowpassfilter.set_cut_frequency(48000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(48000 * 32)
  decimationfilter.set_output_sampling_rate(48000)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_16(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  overfilter = DoubleOversampling6points5order_16Filter()
  overfilter.set_input_sampling_rate(48000)
  overfilter.set_output_sampling_rate(48000 * 16)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleFollowerTransistorClassAFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(48000 * 16)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000 * 16)
  lowpassfilter.set_cut_frequency(48000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(48000 * 16)
  decimationfilter.set_output_sampling_rate(48000)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_8(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  overfilter = DoubleOversampling6points5order_8Filter()
  overfilter.set_input_sampling_rate(48000)
  overfilter.set_output_sampling_rate(48000 * 8)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleFollowerTransistorClassAFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(48000 * 8)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000 * 8)
  lowpassfilter.set_cut_frequency(48000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(48000 * 8)
  decimationfilter.set_output_sampling_rate(48000)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

def filter_4(input):
  import numpy as np
  output = np.zeros(input.shape, dtype=np.float64)

  infilter = DoubleInPointerFilter(input, False)
  infilter.set_input_sampling_rate(48000)
  overfilter = DoubleOversampling6points5order_4Filter()
  overfilter.set_input_sampling_rate(48000)
  overfilter.set_output_sampling_rate(48000 * 4)
  overfilter.set_input_port(0, infilter, 0)
  overdrivefilter = DoubleFollowerTransistorClassAFilter.build_standard_filter()
  overdrivefilter.set_input_sampling_rate(48000 * 4)
  overdrivefilter.set_input_port(0, overfilter, 0)
  lowpassfilter = DoubleButterworthLowPassFilter()
  lowpassfilter.set_input_sampling_rate(48000 * 4)
  lowpassfilter.set_cut_frequency(48000)
  lowpassfilter.set_order(5)
  lowpassfilter.set_input_port(0, overdrivefilter, 0)
  decimationfilter = DoubleDecimationFilter(1)
  decimationfilter.set_input_sampling_rate(48000 * 4)
  decimationfilter.set_output_sampling_rate(48000)
  decimationfilter.set_input_port(0, lowpassfilter, 0)
  outfilter = DoubleOutPointerFilter(output, False)
  outfilter.set_input_sampling_rate(48000)
  outfilter.set_input_port(0, decimationfilter, 0)
  outfilter.process(input.shape[1])
  return output

if __name__ == "__main__":
  import numpy as np
  size = 1200
  
  x = np.arange(size).reshape(1, -1) / 48000.
  d = np.sin(x * 2 * np.pi * 100) * .05
  d.tofile("input2.dat")
  #out = filter_32(d)
  #out.tofile("output32_tca.dat")
  #out = filter_16(d)
  #out.tofile("output16_tca.dat")
  #out = filter_8(d)
  #out.tofile("output8_tca.dat")
  out = filter_4(d)
  out.tofile("output4_tca.dat")

  import matplotlib.pyplot as plt
  plt.plot(x[0], d[0], label="input")
  plt.plot(x[0], out[0], label="output")
  plt.legend()
  plt.show()

