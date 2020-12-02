import tarfile
import os
from winnowing import *

# whenever an input comes and get saved to a user folder : extract => process => get the csv, code similarities, scatter plot => save the csv in the user folder => delete tar and other folders

def extract_and_process(tar_filename):
	directory_of_file = '/'.join(folder for folder in tar_filename.split('/')[:-1])
	# with open(tar_filename) as f:
	# 	f.extractall(directory_of_file)
	mytar = tarfile.open(tar_filename)
	mytar.extractall(directory_of_file)
	mytar.close()


	print("Tar file name is ", tar_filename)
	print(directory_of_file)

	# We are expecting there shall be one directory in the tar file named code_files and one of them shall be named stub_code if stub_code is provided

	print(os.listdir(directory_of_file), "This is the folder presen in the directory")
	print("directory of file is", directory_of_file)

	if "code_files" in os.listdir(directory_of_file):
		code_files_dir = directory_of_file + '/code_files'

		code_files = os.listdir(code_files_dir)

		for i in range(len(code_files)-1):

			for j in range(i+1, len(code_files)):

				print("The similarity between the files are -> ", plagiarismCheck(code_files_dir + '/' + code_files[i], code_files_dir + '/' + code_files[j]))


	


