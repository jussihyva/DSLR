# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scatter_plot.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/22 15:36:38 by jkauppi          ###   ########.fr        #
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
	color_dict = {}
	dataset = pd.read_csv(dataset_file)
	dataset = dataset.dropna()
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	color_dict['Ravenclaw'] = 'blue'
	color_dict['Slytherin'] = 'red'
	color_dict['Gryffindor'] = 'green'
	color_dict['Hufflepuff'] = 'black'
	color_list = []
	for name in dataset['Hogwarts House']:
		color_list.append(color_dict[name])
	color_set = np.array(color_list)
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
