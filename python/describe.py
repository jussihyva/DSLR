# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    describe.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/19 18:40:26 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from CmdArguments import *
from HogwartsSubjects import *

def clculate_quantile(hogwartsSubjects):
	value_list = []
	for course in hogwartsSubjects:
		value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
		value_list_sorted = value_list_sorted.reset_index(drop=True)
		numOfValues = len(value_list_sorted)
		percentile25 = math.ceil(numOfValues * 0.25) - 1
		value_list.append(value_list_sorted[percentile25])
	return ({"25%+": value_list})

def createDescribeList(hogwartsSubjects):
	describe_list = {}
	describe_list.update({"Count": hogwartsSubjects.count()})
	describe_list.update({"Mean": hogwartsSubjects.mean()})
	describe_list.update({"Std": hogwartsSubjects.std()})
	describe_list.update({"Median": hogwartsSubjects.median()})
	describe_list.update({"Min": hogwartsSubjects.min()})
	describe_list.update({"Max": hogwartsSubjects.max()})
	describe_list.update({"1%": hogwartsSubjects.quantile(0.01)})
	describe_list.update({"25%": hogwartsSubjects.quantile(0.25)})
	describe_list.update(clculate_quantile(hogwartsSubjects))
	describe_list.update({"50%": hogwartsSubjects.quantile(0.50)})
	describe_list.update({"75%": hogwartsSubjects.quantile(0.75)})
	describe_list.update({"99%": hogwartsSubjects.quantile(0.99)})
	return (describe_list)

def describe(dataset_file, transpose):
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	describe_list = createDescribeList(hogwartsSubjects_df)
	my_describe_df = pd.DataFrame(describe_list)
	if transpose:
		print(my_describe_df.T)
	else:
		print(my_describe_df)

if __name__ == "__main__":
	cmdArguments = CmdArguments_describe()
	inputParams = cmdArguments.getArguments()
	describe(inputParams.dataset_file, inputParams.Transpose)
