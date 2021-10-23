# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    describe.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/23 16:57:24 by juhani           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pandas.core import indexing
from CmdArguments import *
from HogwartsSubjects import *
from DescribeValidator import *

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
				rankValuePrel = int(numOfValues * int(quantile * 100))
				rankValue = int((rankValuePrel + 50) / 100)
				if inputParams.verbose <= 2:
					print(str(numOfValues) + "   " + course + ": " + str(rankValuePrel) + " : " + str(rankValue))
				if (numOfValues % 2) == 1:
					if int(rankValuePrel / 100) == rankValue:
						value = value_list_sorted[rankValue]
					else:
						value = value_list_sorted[rankValue - 1]
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

	def __calculate_count(self, hogwartsSubjects, validate):
		name = "Count"
		value_list = []
		for course in hogwartsSubjects:
			value_list_sorted = (hogwartsSubjects[course].dropna())
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			value = numOfValues
			value_list.append(value)
		value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
		if validate:
			self.describeValidator.count(hogwartsSubjects, value_series, name)
		return ({name: value_list})

	def __calculate_median(self, hogwartsSubjects, validate, inputParams):
		name = "Median"
		value_list = []
		for course in hogwartsSubjects:
			value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			numOfValues = len(value_list_sorted)
			rankValuePrel = int(numOfValues * 50)
			rankValue = int((rankValuePrel + 50) / 100)
			if inputParams.verbose <= 2:
				print(str(numOfValues) + "   " + course + ": " + str(rankValuePrel) + " : " + str(rankValue))
			if (numOfValues % 2) == 0:
				value = (value_list_sorted[rankValue] + value_list_sorted[rankValue - 1]) / 2
			else:
				value = value_list_sorted[rankValue - 1]
			value_list.append(value)
		value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
		if validate:
			self.describeValidator.median(hogwartsSubjects, value_series, name)
		return ({name: value_list})

	def __sum(self, valueList):
		sum = 0
		for value in valueList:
			sum += value
		return (sum)

	def __variance(self, valueList, mean):
		sum = 0
		for value in valueList:
			sum += abs(value - mean)
		variance = sum / len(valueList)
		return (variance)

	def __calculate_mean(self, hogwartsSubjects, validate):
		name = "Mean"
		value_list = []
		for course in hogwartsSubjects:
			value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			sum = self.__sum(value_list_sorted)
			numOfValues = len(value_list_sorted)
			value = sum / numOfValues
			value_list.append(value)
		value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
		if validate:
			self.describeValidator.mean(hogwartsSubjects, value_series, name)
		return ({name: value_list})

	def __calculate_std(self, hogwartsSubjects, validate):
		name = "Std"
		value_list = []
		for course in hogwartsSubjects:
			value_list_sorted = (hogwartsSubjects[course].dropna()).sort_values()
			value_list_sorted = value_list_sorted.reset_index(drop=True)
			sum = self.__sum(value_list_sorted)
			numOfValues = len(value_list_sorted)
			variance = self.__variance(value_list_sorted, sum / numOfValues)
			value = math.sqrt(variance)
			value = variance
			value_list.append(value)
		value_series = pd.Series(value_list, index=hogwartsSubjects.columns)
		if validate:
			self.describeValidator.std(hogwartsSubjects, value_series, name)
		return ({name: value_list})

	def createDescribeDataFrame(self, hogwartsSubjects, validate):
		describe_list = {}
		describe_list.update(self.__calculate_count(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_mean(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_std(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_median(hogwartsSubjects, validate, inputParams))
		describe_list.update(self.__calculate_min(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_max(hogwartsSubjects, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.01, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.25, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.50, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.75, validate))
		describe_list.update(self.__calculate_percentile(hogwartsSubjects, 0.99, validate))
		return (describe_list)

def describe(dataset_file, inputParams):
	myDescribe = MyDescribe()
	hogwartsSubjects = HogwartsSubjects(dataset_file)
	hogwartsSubjects_df = hogwartsSubjects.getDataFrame()
	describe_list = myDescribe.createDescribeDataFrame(hogwartsSubjects_df, inputParams.Validate)
	my_describe_df = pd.DataFrame(describe_list, index=hogwartsSubjects.getSubjectList())
	if inputParams.Transpose:
		print(my_describe_df)
	else:
		print(my_describe_df.T)

if __name__ == "__main__":
	cmdArguments = CmdArguments_describe()
	inputParams = cmdArguments.getArguments()
	describe(inputParams.dataset_file, inputParams)
