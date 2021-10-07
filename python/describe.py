# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    describe.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/07 14:55:59 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
from CmdArguments import *

def usage():
	print("python3 describe.py dataset_file.csv")

def describe(dataset_file, transpose):
	my_data = pd.read_csv(dataset_file)
	hogwarts_subjects = my_data[["Arithmancy", "Astronomy", "Herbology", \
		"Defense Against the Dark Arts", "Divination", 'Muggle Studies', \
       'Ancient Runes', 'History of Magic', 'Transfiguration', 'Potions', \
       'Care of Magical Creatures', 'Charms', 'Flying']]
	describe_list = {}
	describe_list.update({"Count": hogwarts_subjects.count()})
	describe_list.update({"Mean": hogwarts_subjects.mean()})
	describe_list.update({"Std": hogwarts_subjects.std()})
	describe_list.update({"Median": hogwarts_subjects.median()})
	describe_list.update({"Min": hogwarts_subjects.min()})
	describe_list.update({"Max": hogwarts_subjects.max()})
	describe_list.update({"1%": hogwarts_subjects.quantile(0.01)})
	describe_list.update({"25%": hogwarts_subjects.quantile(0.25)})
	describe_list.update({"50%": hogwarts_subjects.quantile(0.50)})
	describe_list.update({"75%": hogwarts_subjects.quantile(0.75)})
	describe_list.update({"99%": hogwarts_subjects.quantile(0.99)})
	my_describe_df = pd.DataFrame(describe_list)
	# print(hogwarts_subjects["Defense Against the Dark Arts"])
	# hogwarts_subjects = hogwarts_subjects.fillna(hogwarts_subjects.mean())
	# print(hogwarts_subjects["Defense Against the Dark Arts"])
	if transpose:
		print(my_describe_df.T)
	else:
		print(my_describe_df)
	# f, ax = plt.subplots()
	# ax.bar(x=my_data["Index"],
	# 	height=my_data["Arithmancy"],
    #    	color="blue")
	# ax.set(title="Hogwarts")
	# plt.show()

if __name__ == "__main__":
	cmdArguments = CmdArguments()
	inputParams = cmdArguments.get_arguments()
	describe(inputParams.dataset_file, inputParams.Transpose)
