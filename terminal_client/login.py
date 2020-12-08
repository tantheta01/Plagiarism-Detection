import sys
import requests
import pandas as pd
import json
uname = sys.argv[1]
passwd = sys.argv[2]
data = json.dumps({'username' : uname, 'password' : passwd})
headers = {'content-type': 'application/json'}
url = 'http://localhost:8000/api/users/login/'
login_response = requests.post(url, data, headers=headers)

if login_response.status_code != 200:
	print("There was an Error")
	r = login_response.json()
	print(r)
	sys.exit(1)

print("Login Successful")
token = login_response.json()['token']
with open('.secretkey', 'w') as f:
	f.write(token)
sys.exit(0)
