# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hogwartsSubjects.py                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 10:50:45 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/08 11:21:49 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

class HogwartsSubjects():
	def __init__(self, dataset):
		self.subjectList = ["Arithmancy", "Astronomy", "Herbology", \
			"Defense Against the Dark Arts", "Divination", 'Muggle Studies', \
	       'Ancient Runes', 'History of Magic', 'Transfiguration', 'Potions', \
    	   'Care of Magical Creatures', 'Charms', 'Flying']
		self.hogwartsSubjects = dataset[self.subjectList]
	def getDataFrame(self):
		return (self.hogwartsSubjects)
	def getSubjectList(self):
		return (self.subjectList)
