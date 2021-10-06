# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    describe.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:45:44 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/06 17:13:53 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import pandas as pd
import matplotlib.pyplot as plt

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

def describe(dataset_file):
	my_data = pd.read_csv(dataset_file)
	print(my_data.columns)
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
	print(my_describe_df)
	# f, ax = plt.subplots()
	# ax.bar(x=my_data["Index"],
	# 	height=my_data["Arithmancy"],
    #    	color="blue")
	# ax.set(title="Hogwarts")
	# plt.show()

if __name__ == "__main__":
	input_params = read_cmd_arguments()
	describe(input_params["dataset_file"])

