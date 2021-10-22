# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CmdArguments.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 14:46:19 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/22 15:07:33 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import argparse

class CmdArguments:
	def __init__(self):
		pass

	def _create_parser(self, description):
		parser = argparse.ArgumentParser(description = description)
		return parser

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
		parser = self._create_parser("describe prints basic informtion about a content of a dataset file.")
		parser.add_argument("-T", "--Transpose", help = "Transposed printout",
			action=argparse.BooleanOptionalAction, required = False, default = False)
		parser.add_argument("-V", "--Validate", help = "Validate calculations printout",
			action=argparse.BooleanOptionalAction, required = False, default = False)
		parser.add_argument("-v", "--verbose", help = "Print details",
			type=int, required = False, default = 3)
		self._create_arguments(parser)
		return None

class CmdArguments_histogram(CmdArguments):
	def __init__(self):
		CmdArguments.__init__(self)
		parser = self._create_parser("histogram visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_pair(CmdArguments):
	def __init__(self):
		CmdArguments.__init__(self)
		parser = self._create_parser("pair visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_box(CmdArguments):
	def __init__(self):
		CmdArguments.__init__(self)
		parser = self._create_parser("box visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_correlation(CmdArguments):
	def __init__(self):
		CmdArguments.__init__(self)
		parser = self._create_parser("correlation visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None

class CmdArguments_scatter(CmdArguments):
	def __init__(self):
		CmdArguments.__init__(self)
		parser = self._create_parser("scatter visualize basic informtion about a content of a dataset file.")
		self._create_arguments(parser)
		return None
