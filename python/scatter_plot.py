# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scatter_plot.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/08 15:22:00 by jkauppi          ###   ########.fr        #
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
	fig_list = []
	asx_list = []
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	subjectList = hogwartsSubjects.getSubjectList()
	numOfSubjects = len(subjectList)
	for index1 in range(numOfSubjects - 1):
		fig, axs = plt.subplots(1, numOfSubjects - 1 - index1, figsize=(30, 12))
		subject1 = subjectList[index1]
		for index2 in range(index1 + 1, numOfSubjects):
			subject2 = subjectList[index2]
			if subject1 != subject2:
				if (index2 == numOfSubjects - 1) and (index1 == numOfSubjects - 2):
					plt.scatter(hogwartsSubjects_df[subject1], hogwartsSubjects_df[subject2])
					plt.xlabel(subject1)
					plt.ylabel(subject2)
				else:
					axs[index2 - index1 - 1].scatter(hogwartsSubjects_df[subject1], hogwartsSubjects_df[subject2], color=["yellow"])
					axs[index2 - index1 - 1].set_xlabel(subject1)
					axs[index2 - index1 - 1].set_ylabel(subject2)
				# hogwartsSubjects_df.plot.scatter(x = subject1, y = subject2)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_histogram()
	inputParams = cmdArguments.get_arguments()
	scatter_plot(inputParams.dataset_file)
