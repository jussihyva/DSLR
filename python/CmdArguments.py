# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CmdArguments.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/07 14:46:19 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/07 14:56:04 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import argparse

class CmdArguments:
	def __init__(self):
		parser = argparse.ArgumentParser(description = "describe prints basic informtion about a content of a dataset file.")
		parser.add_argument("-T", "--Transpose", help = "Transposed printout", action=argparse.BooleanOptionalAction, required = False, default = False)
		parser.add_argument("dataset_file", help = "Example: Output argument", default = "")
		self.argument = parser.parse_args()

	def get_arguments(self):
		return (self.argument)
