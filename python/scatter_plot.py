# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scatter_plot.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/22 17:36:11 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
from matplotlib import colors
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def scatter_plot(dataset_file):
	hogwartsSubjects = HogwartsSubjects(dataset_file)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	color_set = hogwartsSubjects.getColorSet()
	plot1 = plt.figure(1)
	plt.scatter("Defense Against the Dark Arts", "Astronomy", data=hogwartsSubjects_df, c=color_set)
	plt.title("Correlation of Defense Against the Dark Arts and Astronomy (scatter)")
	plt.xlabel("Defense Against the Dark Arts")
	plt.ylabel("Astronomy")

if __name__ == "__main__":
	cmdArguments = CmdArguments_scatter()
	inputParams = cmdArguments.getArguments()
	scatter_plot(inputParams.dataset_file)
	plt.show()
