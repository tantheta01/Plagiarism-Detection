import sys
import requests
import json
import pandas as pd
import os


try:
	oldpass = sys.argv[1]
	newpass = sys.argv[1]

	with open('.secretkey') as f:
		token = f.read().strip()
	data = json.dumps({'old_password' : oldpass, 'new_password' : newpass})
	headers = { "Content-Type" : "application/json", 'Authorization' : 'Token '+token}
	url = 'http://localhost:8000/api/password/'
	resp = requests.post(url, data, headers=headers)
	if resp.status_code == 200:
		print("password changed successfully")

	else:
		print("There was an error, aborted")
except:
	print("There was an error, Aborted")
os.remove('.secretkey')