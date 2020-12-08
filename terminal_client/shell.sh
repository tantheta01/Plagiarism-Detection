#!/bin/bash

echo "Welcome to Byte Demons Plag Detection"
echo "Press 1 to Sign Up"
echo "Press 2 to Login"
echo "Press any other key to exit"

read choice

if [[ "$choice" == "1" ]]; then
	echo "Enter your user name"
	read username
	echo "Enter your password"
	read -s password
	echo ""
	echo "Re Enter your password"
	read -s repass
	echo ""
	echo "Enter your Email"
	read email
	if [[ "$repass" == "$password" ]]; then
		python3 signup.py "$username" "$password" "$email"
	else
		echo "Passwords did not match, aborted"
	fi
elif [[ "$choice" == "2" ]]; then
	echo "Enter Your username"
	read username
	echo "Enter Your Password"
	read -s password
	python3 login.py "$username" "$password"

	if [[ "$?" == "$((1))" ]]; then
		echo "Goodbye"
	else
		echo "Press 1 to upload and check files"
		echo "Press 2 to Change password"
		read choice
		if [[ "$choice" == "1" ]]; then
			echo "Give the complete path of the file"
			read path
			python3 upload.py "$path"
		elif [[ "$choice" == "2" ]]; then
			
			echo "Enter Your old password"
			read -s olpass
			echo "Enter your newpassword"
			read -s passwd
			echo ""
			echo "Re Enter new password"
			read -s repass
			echo ""
			if [[ "$repass" == "$passwd" ]]; then
				python3 changepass.py "$passwd" "$newpass"
			else
				echo "Passwords don't match"
			fi
		else
			echo "Not a valid input"
			rm .secretkey
		fi
	fi


	echo "Good Bye"
fi

