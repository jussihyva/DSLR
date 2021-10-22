# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    box_plot.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 10:24:10 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/22 17:56:38 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import math
from matplotlib import colors
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def box_plot(dataset_file):
	hogwartsSubjects = HogwartsSubjects(dataset_file)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	numOfSubjects = hogwartsSubjects.getNumOfSubjects()
	columns = math.ceil(np.sqrt(hogwartsSubjects_df.shape[1]))
	rows = math.ceil(hogwartsSubjects_df.shape[1] / columns)
	title = "Overview of Hogwards courses (Boxplot)"
	hogwartsSubjects_df.plot(kind='box', subplots=True,
		layout=(rows, columns), sharex=False, sharey=False, title=title)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_box()
	inputParams = cmdArguments.getArguments()
	box_plot(inputParams.dataset_file)
