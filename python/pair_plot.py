# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pair_plot.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/24 11:26:29 by juhani           ###   ########.fr        #
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
	houses = hogwartsSubjects.getHouses()
	axes = pd.plotting.scatter_matrix(hogwartsSubjects_df, alpha=0.2, 
		diagonal="kde", color=color_set, label=houses)
	axes = axes.flatten()
	subjectList = hogwartsSubjects.getSubjectList()
	for i in range(0, len(axes)):
		axes[i].xaxis.label.set_rotation(30)
		axes[i].yaxis.label.set_rotation(0)
		axes[i].set_xticklabels([])
		axes[i].set_yticklabels([])
	# 	axes[i].legend(houses)

	# plt.legend([axes],     # The line objects
	# 	labels=houses,   # The labels for each line
	# 	loc="center right",   # Position of legend
	# 	borderaxespad=0.1,    # Small spacing around legend box
	# 	title="Legend Title"  # Title for the legend
	# 	)


	# handles, labels = axes[len(axes) - 1].get_legend_handles_labels()
	# plt.legend(handles, labels)
	title = "Overview of Hogwards courses (pair)"
	plt.suptitle(title)
	plt.tight_layout()
	plt.gcf().subplots_adjust(wspace=0, hspace=0)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_pair()
	inputParams = cmdArguments.getArguments()
	pair_plot(inputParams.dataset_file)
