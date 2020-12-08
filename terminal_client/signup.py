import sys
import requests
import json
uname = sys.argv[1]
passwd = sys.argv[2]
email = sys.argv[3]

res = requests.post('http://localhost:8000/api/users/', json.dumps({'username' : uname, 'password' : passwd, 'email': email}), headers={'content-type': 'application/json'})

if res.status_code != 201:
	print("There was an error!")
	if 'username' in res.json().keys():
		print("Username :", res.json()['username'][0])
	if 'password' in res.json().keys():
		print("Password :", res.json()['password'][0])
	if 'email' in res.json().keys():
		print("Email :", res.json()['email'][0])
	sys.exit()

print("Sign Up Successful")