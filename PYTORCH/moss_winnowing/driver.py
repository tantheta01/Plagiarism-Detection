import tarfile
import os
import shutil
import numpy as np
from winnowing import *
from plot import get_reduced_components


def CountFrequency(my_list): 
  
    # Creating an empty dictionary  
    freq = {} 
    for item in my_list: 
        if (item in freq): 
            freq[item] += 1
        else: 
            freq[item] = 1

    return [element[1] for element in freq.items()]


def getExclusiveSimilarity(file1, file2): 

	"""! @brief Evaluates the exclusive similarity between two files.  
	 	
		
		@param file1 : The similarity between the code and another code
		@param file2 : The similarity between the code and stub code
		
		@return file1_f : The similarity exclusive for the two files
	"""

	file1_chunks = file1.split("<mark>")
	file2_chunks = file2.split("<mark>")

	y1 = file1.substr(0,6)!="<mark>"
	y2 = file2.substr(0,6)!="<mark>"

	file1_ranges=[]
	file2_ranges=[]
	f1_start_idx=0
	f2_start_idx=0

	for i in len(len(file1_chunks)):
		if i%2 == y1:
			file1_ranges.append((f1_start_idx, f1_start_idx+len(file1_chunks[i])))

		f1_start_idx += len(file1_chunks[i])

	for i in range(len(file2_chunks)):
		if i%2 == y2:
			file2_ranges.append((f2_start_idx, f2_start_idx+len(file2_chunks[i])))

		f2_start_idx += len(file2_chunks[i])

	
	f2_block=0
	f1_exc_blocks=[]
	for i in range(len(file1_ranges)):
		startx, endx = file1_ranges[i]
		while f2_block<len(file2_ranges) and file2_ranges[f2_block][1] <= startx:
			f2_block+=1
		if f2_block == len(file2_ranges):
			f1_exc_blocks += file1_ranges[i:]
			break

		elif file2_ranges[f2_block][0] >= endx:
			f1_exc_blocks.append((startx, endx))
		elif file2_ranges[f2_block][0]>=startx:
			if endx <= file2_ranges[f2_block][1]:
				f1_exc_blocks.append(startx, file2_ranges[f2_block][0])
			elif endx > file2_ranges[f2_block][1]:
				while f2_block < len(file2_ranges) and endx > file2_ranges[f2_block][1]:
					f1_exc_blocks.append(max(startx, file2_ranges[f2_block][0]), min(endx, file2_ranges[f2_block][1]))
					startx=min(endx, file2_ranges[f2_block][1])
					f2_block+=1
		else:
			if endx <= file2_ranges[f2_block][1]:
				continue
			else:
				f1_exc_blocks.append((file2_ranges[f2_block][1], endx))

	merged_ranges=[]
	cend=0
	for x in f1_exc_blocks:
		if x[0] < x[1]:
			if x[0]<=cend:
				merged_ranges[len(merged_ranges)-1][1] = max(merged_ranges[len(merged_ranges)-1][1], x[1])
				cend = merged_ranges[len(merged_ranges)-1][1]
			else:
				merged_ranges.append(x)
				cend = x[1]

	file1_unmarked = ''.join(x for x in file1_chunks)
	start=0
	plagged=0
	file1_f = file1_unmarked[:merged_ranges[0][0]]
	for i in range(len(merged_ranges)):
		if merged_ranges[i][0] < merged_ranges[i][1]:
			file1_f = file1_f + "<mark>" + file1_unmarked[merged_ranges[i][0] : merged_ranges[i][1]] + "<mark>"
			plagged += merged_ranges[i][1]-merged_ranges[i][0]
			if i < len(merged_ranges)-1:
				file1_f = file1_f + file1_unmarked[merged_ranges[i][1] : merged_ranges[i+1][0]]
			else:
				file1_f = file1_f + file1_unmarked[merged_ranges[i][1] : ]
	return plagged/len(file1_unmarked), file1_f


def extract_and_process(tar_filename):

	"""!
	@brief Driver Circuit to extract tar files and pass them through prepreocessing. 

	@param tar_filename : path of the tar file containing code files to be checked
	@return file_similarities : a dictionary of the form (file1_name, file2_name) : {'first_file' : first_file, 'second_file' : second_file, 'similarity' : similarity }. 
	The key tuple has been stringified for easy usage. 
	@return code_files : list of files in the directory code_files
	@return sorted_list : List of file pair similarities sorted in decreasing order of similarity
	@return embedded_files 2 Dimentional embeddings for every file for better visualization
	@return binned list containing the number of pairs of file similar in the bins of width 0.2 each 
	"""

	directory_of_file = '/'.join(folder for folder in tar_filename.split('/')[:-1])
	# with open(tar_filename) as f:
		# f.extractall(directory_of_file)
	mytar = tarfile.open(tar_filename)
	mytar.extractall(directory_of_file)
	mytar.close()

	# print("Tar file name is ", tar_filename)
	# print(directory_of_file)

	file_similarities = {}

	# We are expecting there shall be one directory in the tar file named code_files and one named stub_code if stub_code is provided

	file1=[]
	file2=[]
	similarity=[]

	code_files_dir = directory_of_file + '/code_files'
	code_files = os.listdir(code_files_dir)
	isLangSpec = code_files[0].split('.')[-1] == 'java'
	file_params = [getFingerPrints(directory_of_file + '/code_files/' + file, isLangSpec) for file in code_files]
	freq_fingerprints = [CountFrequency(param[3]) for param in file_params]
	embedded_files = get_reduced_components(freq_fingerprints)
	# print(embedded_files)



	if "stub_code" in os.listdir(directory_of_file):

		stub_code_file = directory_of_file + "/stub_code/" + os.listdir(directory_of_file + "/stub_code")[0]
		stub_code_params = getFingerPrints(stub_code_file)

		code_files_dir = directory_of_file + '/code_files'
		code_files = os.listdir(code_files_dir)

		code_files_similarity_stub_code = []

		for i in range(len(code_files)):
			_, file_com = plagiarismCheck(code_files_dir + '/' + code_files[i], file_params[i][0], file_params[i][1], file_params[i][2], file_params[i][3], stub_code_params[3])
			code_files_similarity_stub_code.append(file_com)

		for i in range(len(code_files)-1):

			for j in range(i+1, len(code_files)):

				file1_sim, file1_com = plagiarismCheck(code_files_dir + '/' + code_files[i], file_params[i][0], file_params[i][1], file_params[i][2], file_params[i][3], file_params[j][3])
				file1_sim, file1_com = getExclusiveSimilarity(file1_com, code_files_similarity_stub_code[i])

				file2_sim, file2_com = plagiarismCheck(code_files_dir + '/' + code_files[j], file_params[j][0], file_params[j][1], file_params[j][2], file_params[j][3], file_params[j][3])
				file2_sim, file2_com = getExclusiveSimilarity(file2_com, code_files_similarity_stub_code[j])

				file_similarities[(code_files[i], code_files[j])] = {"first_file" : file1_com, "second_file" : file2_com, "similarity" : min(file1_sim, file2_sim)}
				file_similarities[(code_files[j], code_files[i])] = {"first_file" : file2_com, "second_file" : file1_com, "similarity" : min(file1_sim, file2_sim)}

				file1.append(code_files[i])
				file2.append(code_files[j])
				similarity.append(min(file1_sim,file2_sim))

		file_similarities = {','.join(k):v for (k,v) in sorted(file_similarities.items(), key = lambda item : -1*item[1]["similarity"])}
		shutil.rmtree(directory_of_file + "/stub_code")


	else:
		code_files_dir = directory_of_file + '/code_files'

		code_files = os.listdir(code_files_dir)

		for i in range(len(code_files)-1):

			for j in range(i+1, len(code_files)):

				file1_sim, file1_com = plagiarismCheck(code_files_dir + '/' + code_files[i], file_params[i][0], file_params[i][1], file_params[i][2], file_params[i][3], file_params[j][3])
				# print(len(file1_com.split("<mark>")))
				file2_sim, file2_com = plagiarismCheck(code_files_dir + '/' + code_files[j], file_params[j][0], file_params[j][1], file_params[j][2], file_params[j][3], file_params[i][3])

				file_similarities[(code_files[i], code_files[j])] = {"first_file" : file1_com, "second_file" : file2_com, "similarity" : min(file1_sim, file2_sim)}
				file_similarities[(code_files[j], code_files[i])] = {"first_file" : file2_com, "second_file" : file1_com, "similarity" : min(file1_sim, file2_sim)}

				file1.append(code_files[i])
				file2.append(code_files[j])
				similarity.append(min(file1_sim,file2_sim))


		file_similarities = {','.join(k):v for (k,v) in sorted(file_similarities.items(), key = lambda item : -1*item[1]["similarity"])}
		
	shutil.rmtree(directory_of_file + "/code_files")
	os.remove(tar_filename)

	csv_list = np.column_stack([np.array(file1), np.array(file2), np.array(similarity)])
	sorted_list = csv_list[np.argsort(csv_list[:, 2])][::-1]

	return file_similarities, code_files, sorted_list, embedded_files


