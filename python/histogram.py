# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    histogram.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 18:49:56 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/08 11:12:27 by jkauppi          ###   ########.fr        #
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

def histogram(dataset_file):
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	pd.DataFrame.hist(hogwartsSubjects_df)
	plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments_histogram()
	inputParams = cmdArguments.get_arguments()
	histogram(inputParams.dataset_file)
