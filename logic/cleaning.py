# This file implements the functions for cleaning the input file

# For language generic detection:

import os
import errno
import re
import sys

not_var_name = ['"', "'", ';', ':', '!', ]

# read a file and remove the equality operator and LHS 
def removeequality(filename):

	if not filename or not os.path.isfile(filename):
		raise FileNotFoundError(errno.ENOENT, os.strerror(errno.ENOENT), filename)
	# cur_path = os.listdir()
	# print(cur_path)
	# print("haha")
	with open(filename) as f:
		fileLines = f.readlines()
	fileLines = [k.strip() for k in fileLines]
	equality_expression = re.compile(r'([a-zA-Z_$][a-zA-Z_$0-9]*)(\s)*=')
	empty_expression = ''
	fileLines = [equality_expression.sub(empty_expression, k) for k in fileLines]
	return [k.strip() for k in fileLines if len(k)>2]
	# One more thing to add : remove lines which are just constant numbers

	return [k.strip() for k in fileLines if len(k)>2 and not k.isdigit()]



# provides the lines from line1 and line2 (not inclusing line2) in the form of a string with removed new lines
def selectlines(line1, line2, fileLines):
	return ''.join(fileLines[i] for i in range(line1, line2))


# This takes two file lines and yields a pair of strings each some lines long
# def getData(fileLines1, fileLines2, minSize):

# 	for i in range(minSize, min(len(fileLines1), len(fileLines2))+1):


def selectAllLines(fileLines):

	return ''.join(line for line in fileLines)


def integrate():

	fileLines = removeequality(sys.argv[1])
	fString = selectAllLines(fileLines)
	with open(sys.argv[2], 'w') as f:
		f.write(fString)

		

if __name__ == '__main__':
	integrate()