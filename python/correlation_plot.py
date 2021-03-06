# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    correlation_plot.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 10:38:42 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/22 17:51:22 by jkauppi          ###   ########.fr        #
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

def correlation_plot(dataset_file):
	hogwartsSubjects = HogwartsSubjects(dataset_file)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	subjects = hogwartsSubjects.getSubjectList()
	numOfSubjects = hogwartsSubjects.getNumOfSubjects()
	correlations = hogwartsSubjects_df.corr()
	fig = plt.figure()
	ax = fig.add_subplot(111)
	cax = ax.matshow(correlations, vmin=-1, vmax=1)
	fig.colorbar(cax)
	ticks = np.arange(0, numOfSubjects, 1)
	title = "Overview of Hogwards courses (Correlations)"
	fig.suptitle(title)
	ax.set_xticks(ticks)
	ax.set_yticks(ticks)
	ax.set_xticklabels(subjects, rotation=20)
	ax.set_yticklabels(subjects)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_correlation()
	inputParams = cmdArguments.getArguments()
	correlation_plot(inputParams.dataset_file)
