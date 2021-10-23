# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    HogwartsSubjects.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhani <juhani@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 10:50:45 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/23 17:46:50 by juhani           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import pandas as pd
import numpy as np

class HogwartsSubjects():
	def __init__(self, dataset_file):
		dataset = pd.read_csv(dataset_file)
		self.subjectList = ["Arithmancy", "Astronomy", "Herbology", \
			"Defense Against the Dark Arts", "Divination", 'Muggle Studies', \
	       'Ancient Runes', 'History of Magic', 'Transfiguration', 'Potions', \
    	   'Care of Magical Creatures', 'Charms', 'Flying']
		self.hogwartsSubjects = dataset[self.subjectList]
		self.color_set = self.__create_color_list(dataset)
		self.subjectListLen = len(self.subjectList)
		self.hogwartsHouses = dataset["Hogwarts House"]
		self.houseList = ["Ravenclaw", "Slytherin", "Gryffindor", "Hufflepuff"]

	def __create_color_list(self, dataset):
		color_dict = {}
		color_dict['Ravenclaw'] = 'blue'
		color_dict['Slytherin'] = 'red'
		color_dict['Gryffindor'] = 'green'
		color_dict['Hufflepuff'] = 'black'
		color_list = []
		for name in dataset['Hogwarts House']:
			color_list.append(color_dict[name])
		color_set = np.array(color_list)
		return (color_set)

	def getColorSet(self):
		return (self.color_set)

	def getDataFrame(self):
		return (self.hogwartsSubjects)

	def getSubjectList(self):
		return (self.subjectList)

	def getHouseList(self):
		return (self.houseList)

	def getNumOfSubjects(self):
		return (self.subjectListLen)

	def getHouses(self):
		return (self.hogwartsHouses)
