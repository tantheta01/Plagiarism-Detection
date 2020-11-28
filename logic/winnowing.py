# This file shall have the functions to hash and perform winnowing for the input file strings
import hashlib
import sys

def getHashes(fileString):
	try:
		kgrams = [fileString[i:i+5] for i in range(len(fileString)-5)]
		hashes = [int(hashlib.sha256(s.encode('utf-8')).hexdigest(), 16) % 10**8 for s in kgrams]
		return hashes
	except TypeError:
		raise


if __name__ == '__main__':
	with open(sys.argv[1]) as f:
		string = f.read()

	h = getHashes(string)
	w = 50
	ourList = []

	fnum = 0
	findex = -1
	

	for i in range(50):
		if h[i] >= fnum:
			findex = i
			fnum = h[i]

	ourList.append(fnum)
	for k in range(w, len(h)):
		if h[k] >= fnum:
			fnum = h[k]
			findex = k
			ourList.append(fnum)

		elif findex+w<=k:
			fnum=-1
			for j in range(50):
				if h[k-w+1+j] >= fnum:
					fnum = h[k-w+1+j]
					findex = k-w+1+j
			ourList.append(fnum)




	with open(sys.argv[2],'w') as g:
		g.write(str(getHashes(string)))


		# print("bc   ", findex, k)
