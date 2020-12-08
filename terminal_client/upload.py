import sys
import requests
import json
import pandas as pd
import os


try:
	path = sys.argv[1]
	# print("path", path)
	fname = path.split('/')[-1]
	# print("fname", fname)
	with open('.secretkey') as f:
		token = f.read().strip()
	# print("Token", token)
	url2 = 'http://localhost:8000/api/files/upload/' + fname
	files = {'file': open(path, 'rb')}
	# print("url2")
	headers = {'Authorization' : 'Token '+token}
	r = requests.post(url2, files=files, headers=headers)


	if r.status_code == 200:
		# print("Yes here")
		csvf = r.json()['csv']
		print('Enter directory to store results')
		path2 = input()
		print(path2)
		print(path2[-1])
		if path2[-1] == '/':
			path2 = path2[:-1]
		df = pd.DataFrame(list(zip(csvf['0'], csvf['1'], csvf['2'])), columns=['File1', 'File2', 'Similarity'])
		print(df)
		print('Writing results to : ', path2 + '/results.csv')
		df.to_csv(path2 + '/results.csv')

	else:
		print("There was an error")

	os.remove('.secretkey')
except:
	print("There was an error")

sys.exit()


