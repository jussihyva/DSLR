# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scatter_plot.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 19:16:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/08 11:25:29 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def usage():
	print("python3 describe.py dataset_file.csv")

def read_cmd_arguments():
	input_params = {}
	if len(sys.argv) != 2:
		usage()
		exit(42)
	else:
		input_params.update({"dataset_file": sys.argv[1]})
	return (input_params)

def scatter_plot(dataset_file):
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	subjectList = hogwartsSubjects.getSubjectList()
	subject1 = subjectList[0]
	for subject2 in subjectList:
		hogwartsSubjects_df.plot.scatter(x = subject1, y = subject2)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_histogram()
	inputParams = cmdArguments.get_arguments()
	scatter_plot(inputParams.dataset_file)
