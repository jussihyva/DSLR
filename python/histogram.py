# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    histogram.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 18:49:56 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/23 23:22:27 by juhani           ###   ########.fr        #
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
	subjectList = hogwartsSubjects.getSubjectList()
	houses = hogwartsSubjects.getHouses()
	for i in range(0, hogwartsSubjects.getNumOfSubjects()):
		for house in hogwartsSubjects.getHouseList():
			houseIndexList = houses.where(houses == house).dropna().index
			axes[i].hist(hogwartsSubjects_df[subjectList[i]][houseIndexList],
				alpha=0.3)
		axes[i].set_title(subjectList[i])
		axes[i].legend(houses)
	title = "Overview of Hogwards courses (Histogram)"
	plt.suptitle(title)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_histogram()
	inputParams = cmdArguments.getArguments()
	histogram(inputParams.dataset_file)
