# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scatter_plot.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/15 09:34:04 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
from matplotlib import colors
import pandas as pd
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def scatter_plot(dataset_file):
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	axes = pd.plotting.scatter_matrix(hogwartsSubjects_df, alpha=0.2, 
		diagonal="kde")
	for ax in axes.flatten():
		ax.xaxis.label.set_rotation(30)
		ax.yaxis.label.set_rotation(0)
		ax.set_xticklabels([])
		ax.set_yticklabels([])
	title = "Overview of Hogwards courses (Scatter)"
	plt.suptitle(title)
	plt.tight_layout()
	plt.gcf().subplots_adjust(wspace=0, hspace=0)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_scatter()
	inputParams = cmdArguments.getArguments()
	scatter_plot(inputParams.dataset_file)
