# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    describe.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/21 11:45:48 by jkauppi          ###   ########.fr        #
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

class DescribeValidator():
	def __init__(self) -> None:
		pass
	def percentile(self, hogwartsSubjects, value_series, quantile, name):
		ref_list = hogwartsSubjects.quantile(quantile, interpolation="lower")
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")

	def max(self, hogwartsSubjects, value_series, name):
		ref_list = hogwartsSubjects.max()
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")

	def min(self, hogwartsSubjects, value_series, name):
		ref_list = hogwartsSubjects.min()
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")

class MyDescribe():
	def __init__(self):
		self.interpolation = "lower"
		self.describeValidator = DescribeValidator()
	def __calculate_percentile(self, hogwartsSubjects, quantile, validate):
		name = str(int(quantile * 100)) + "%"
		value_list = []
		if self.interpolation == "lower":
			for course in hogwartsSubjects:
				value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
				value_list_sorted = value_list_sorted.reset_index(drop=True)
				numOfValues = len(value_list_sorted)
				rankValuePrel = numOfValues * quantile
				# print(str(numOfValues) + "   " + course + ": " + str(rankValuePrel))
				rankValue = round(numOfValues * quantile)
				if (numOfValues % 2) == 1:
					if (int(rankValuePrel) % 2) == 2:
						value = value_list_sorted[rankValue - 1]
					# elif ((rankValue % 2) == 1) and (int(rankValuePrel) == rankValue):
					# 	value = value_list_sorted[rankValue - 1]
					elif int(rankValuePrel) == rankValue:
						value = value_list_sorted[rankValue]
					else:
						value = value_list_sorted[rankValue - 1]
				elif ((numOfValues % 2) == 1) and ((int(rankValuePrel) % 2) == 0):
					value = value_list_sorted[rankValue]
				else:
					value = value_list_sorted[rankValue - 1]
				value_list.append(value)
			value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
			if validate:
				self.describeValidator.percentile(hogwartsSubjects, value_series, quantile, name)
		return ({name: value_list})

	def __calculate_max(self, hogwartsSubjects, validate):
		name = "Max"
		value_list = []
		for course in hogwartsSubjects:
			value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			value = value_list_sorted[numOfValues - 1]
			value_list.append(value)
		value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
		if validate:
			self.describeValidator.max(hogwartsSubjects, value_series, name)
		return ({name: value_list})

	def __calculate_min(self, hogwartsSubjects, validate):
		name = "Min"
		value_list = []
		for course in hogwartsSubjects:
			value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			value = value_list_sorted[0]
			value_list.append(value)
		value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
		if validate:
			self.describeValidator.min(hogwartsSubjects, value_series, name)
		return ({name: value_list})

	def createDescribeDataFrame(self, hogwartsSubjects, validate):
		describe_list = {}
		describe_list.update({"Count": hogwartsSubjects.count()})
		describe_list.update({"Mean": hogwartsSubjects.mean()})
		describe_list.update({"Std": hogwartsSubjects.std()})
		describe_list.update({"Median": hogwartsSubjects.median()})
		describe_list.update(self.__calculate_min(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_max(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.01, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.25, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.50, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.75, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.99, validate))
		return (describe_list)

def describe(dataset_file, transpose, validate):
	myDescribe = MyDescribe()
	dataset = pd.read_csv(dataset_file)
	hogwartsSubjects = HogwartsSubjects(dataset)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	describe_list = myDescribe.createDescribeDataFrame(hogwartsSubjects_df, validate)
	my_describe_df = pd.DataFrame(describe_list)
	if transpose:
		print(my_describe_df.T)
	else:
		print(my_describe_df)

if __name__ == "__main__":
	cmdArguments = CmdArguments_describe()
	inputParams = cmdArguments.getArguments()
	describe(inputParams.dataset_file, inputParams.Transpose, inputParams.Validate)
