# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    histogram.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 18:49:56 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/06 19:17:12 by jkauppi          ###   ########.fr        #
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

def histogram(dataset_file):
	my_data = pd.read_csv(dataset_file)
	hogwarts_subjects = my_data[["Arithmancy", "Astronomy", "Herbology", \
		"Defense Against the Dark Arts", "Divination", 'Muggle Studies', \
       'Ancient Runes', 'History of Magic', 'Transfiguration', 'Potions', \
       'Care of Magical Creatures', 'Charms', 'Flying']]
	histogram_list = {}
	histogram_list.update({"Count": hogwarts_subjects.count()})
	histogram_list.update({"Mean": hogwarts_subjects.mean()})
	histogram_list.update({"Std": hogwarts_subjects.std()})
	histogram_list.update({"Median": hogwarts_subjects.median()})
	histogram_list.update({"Min": hogwarts_subjects.min()})
	histogram_list.update({"Max": hogwarts_subjects.max()})
	histogram_list.update({"1%": hogwarts_subjects.quantile(0.01)})
	histogram_list.update({"25%": hogwarts_subjects.quantile(0.25)})
	histogram_list.update({"50%": hogwarts_subjects.quantile(0.50)})
	histogram_list.update({"75%": hogwarts_subjects.quantile(0.75)})
	histogram_list.update({"99%": hogwarts_subjects.quantile(0.99)})
	my_histogram_df = pd.DataFrame(histogram_list)
	# print(hogwarts_subjects["Defense Against the Dark Arts"])
	# hogwarts_subjects = hogwarts_subjects.fillna(hogwarts_subjects.mean())
	# print(hogwarts_subjects["Defense Against the Dark Arts"])
	pd.DataFrame.hist(hogwarts_subjects)
	plt.show()

if __name__ == "__main__":
	input_params = read_cmd_arguments()
	histogram(input_params["dataset_file"])
