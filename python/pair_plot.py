# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pair_plot.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/24 16:21:58 by juhani           ###   ########.fr        #
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
	houses = hogwartsSubjects.getHouseList()
	axes = pd.plotting.scatter_matrix(hogwartsSubjects_df, alpha=0.2, 
		diagonal="kde", color=color_set)
	axes = axes.flatten()
	subjectList = hogwartsSubjects.getSubjectList()
	for i in range(0, len(axes)):
		axes[i].xaxis.label.set_rotation(30)
		axes[i].yaxis.label.set_rotation(0)
		axes[i].set_xticklabels([])
		axes[i].set_yticklabels([])
	color_list = ["blue", "red", "green", "black"]
	handles = [plt.plot([],[],color=color_list[i], ls="", marker=".", \
		markersize=12)[0] for i in range(4)]
	labels=houses
	plt.legend(handles, labels, loc=(1.02,0))
	title = "Overview of Hogwards courses (pair)"
	plt.suptitle(title)
	plt.tight_layout()
	plt.gcf().subplots_adjust(wspace=0, hspace=0)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_pair()
	inputParams = cmdArguments.getArguments()
	pair_plot(inputParams.dataset_file)
