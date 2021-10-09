# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CmdArguments.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 14:46:19 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/09 15:03:19 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import argparse

class CmdArguments:
	def __init__(self):
		pass

	def __add_common_arguments(self, parser):
		parser.add_argument("dataset_file", help = "Dataset file", default = "")
		return None

	def _create_arguments(self, parser):
		self.__add_common_arguments(parser)
		self.arguments = parser.parse_args()
		return None

	def getArguments(self):
		return (self.arguments)

class CmdArguments_describe(CmdArguments):
	def __init__(self):
		CmdArguments.__init__(self)
		parser = argparse.ArgumentParser(description = "describe prints basic informtion about a content of a dataset file.")
		parser.add_argument("-T", "--Transpose", help = "Transposed printout", action=argparse.BooleanOptionalAction, required = False, default = False)
		self._create_arguments(parser)
		return None

class CmdArguments_histogram(CmdArguments):
	def __init__(self):
		parser = argparse.ArgumentParser(description = "histogram visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_scatter(CmdArguments):
	def __init__(self):
		parser = argparse.ArgumentParser(description = "scatter visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_box(CmdArguments):
	def __init__(self):
		parser = argparse.ArgumentParser(description = "whisker visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_correlation(CmdArguments):
	def __init__(self):
		parser = argparse.ArgumentParser(description = "correlation visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None
