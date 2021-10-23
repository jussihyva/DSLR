# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pair_plot.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/23 22:43:41 by juhani           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
from matplotlib import colors
from numpy.core.fromnumeric import mean
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def pair_plot(dataset_file):
	hogwartsSubjects = HogwartsSubjects(dataset_file)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	color_set = hogwartsSubjects.getColorSet()
	hogwartsSubjects_df = hogwartsSubjects_df.fillna(hogwartsSubjects_df.mean())
	axes = pd.plotting.scatter_matrix(hogwartsSubjects_df, alpha=0.2, 
		diagonal="kde", color=color_set)
	for ax in axes.flatten():
		ax.xaxis.label.set_rotation(30)
		ax.yaxis.label.set_rotation(0)
		ax.set_xticklabels([])
		ax.set_yticklabels([])
	title = "Overview of Hogwards courses (pair)"
	plt.suptitle(title)
	plt.tight_layout()
	plt.gcf().subplots_adjust(wspace=0, hspace=0)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_pair()
	inputParams = cmdArguments.getArguments()
	pair_plot(inputParams.dataset_file)
