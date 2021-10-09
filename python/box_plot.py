# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    box_plot.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 10:24:10 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/09 15:55:55 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
from matplotlib import colors
import pandas as pd
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def box_plot(dataset_file):
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	numOfSubjects = hogwartsSubjects.getNumOfSubjects()
	columns = round(sqrt(hogwartsSubjects_df.shape[1]))
	title = "Overview of Hogwards courses (Boxplot)"
	hogwartsSubjects_df.plot(kind='box', subplots=True,
		layout=(columns, 4), sharex=False, sharey=False, title=title)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_box()
	inputParams = cmdArguments.getArguments()
	box_plot(inputParams.dataset_file)
