# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    histogram.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 18:49:56 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/23 11:53:40 by juhani           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *
import math

def histogram(dataset_file):
	hogwartsSubjects = HogwartsSubjects(dataset_file)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	fig, axes = plt.subplots(4,4)
	axes = axes.flatten()
	color_set = hogwartsSubjects.getColorSet()
	getSubjectList = hogwartsSubjects.getSubjectList()
	for i in range(0, hogwartsSubjects.getNumOfSubjects()):
		axes[i].hist(hogwartsSubjects_df[getSubjectList[i]])
	title = "Overview of Hogwards courses (Histogram)"
	columns = math.ceil(np.sqrt(hogwartsSubjects_df.shape[1]))
	rows = math.ceil(hogwartsSubjects_df.shape[1] / columns)
#	hogwartsSubjects_df.plot(kind='hist', subplots=False,
#		layout=(rows, columns), sharex=False, sharey=False, title=title)
#	hogwartsSubjects_df.plot(kind='hist', subplots=True,
#		layout=(rows, columns), sharex=False, sharey=False, title=title, color="read")
	plt.suptitle(title)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_histogram()
	inputParams = cmdArguments.getArguments()
	histogram(inputParams.dataset_file)
