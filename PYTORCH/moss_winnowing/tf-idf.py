from winnowing import *


def find_match(all_filenames):
	"""
	This function takes as input a list of files in all_filenames and finds matches in all file pairs. Thenn we apply tfidf to see which of the hashes are significant
	"""
	matchings_per_file[]
	for i in len(all_filenames):
		matchings_per_file.append([])

	matching_per_pair = {}

	for (i, filename) in enumerate(all_filenames): #iterate over all files and check them to each other. Store a file's similarity with every file

		for j in range(i+1, len(all_filenames)):

			matched_hashes, newcode = plagiarismCheck(all_filenames[i], all_filenames[j])
			first_hashes = [(i[1], i[2]) for i in matched_hashes]
			second_hashes = [(i[3], i[4]) for i in matched_hashes]
			first_hashes.sort()

