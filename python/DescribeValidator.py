# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    DescribeValidator.py                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 12:53:56 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/21 13:50:21 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

	def count(self, hogwartsSubjects, value_series, name):
		ref_list = hogwartsSubjects.count()
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")

	def mean(self, hogwartsSubjects, value_series, name):
		ref_list = hogwartsSubjects.mean()
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")

	def median(self, hogwartsSubjects, value_series, name):
		ref_list = hogwartsSubjects.median()
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")

	def std(self, hogwartsSubjects, value_series, name):
		ref_list = hogwartsSubjects.std()
		result = value_series.compare(ref_list)
		if result.empty:
			print(name + ": OK")
		else:
			print(name + ": NOT OK")
			print("START (details)")
			print(result)
			print("END")
