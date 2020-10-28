# Plagiarism-Detection
A simple client to detect source code plagiarism detection using various techniques

<<<<<<< HEAD

## Core Logic


## Frontend : (Picture daal denge front end ki)
The front end has been implemented in Angular and allows 	


## Backend







## The Big Picture
=======
## Project implemented so far
### Frontend

The frontend is implemented in Angular, Javascript library. On loading the application directs to a Get Started page which has a small description about the project and a link to the login page. The login page asks the user for the username and password. If the user doesn’t have an account already they can be directed to the registration page. After a successful login, the user is directed to the mainpage which has all the features in a single dashboard. It displays the user profile and has a description for (how to use the webapp) like a link. It has options for file uploading which directs the user to a file upload page where the user can upload the file(s) to be checked and then view the result in the form of graphs and visualization. It also has an option for the user to view previous results for the file(s) that have been checked before. The person can also edit the profile using the “Edit profile” option on the mainpage.
All the pages apart from the “View Result” page have been implemented in the current version.

#image to be added

### Backend
To be added

## Technologies and Frameworks used
The frontend is implemented in Angular and backend with Django framework and Django REST framework. 

### API Used
Four APIs have been used:
- Login
- Register/Sign up
- File Upload
- Change password

## Project Setup

- Clone this github repository on your local machine using `git clone https://github.com/tantheta01/Plagiarism-Detection`
- cd into the repository and then in the backend folder, `PYTORCH` and run the following command
  
  `python3 manage.py runserver`
  
  This will set up the backend environment on your local machine.
- To run the frontend locally, first cd out of the backend folder and then cd into the frontend folder i.e. `FrontEnd/sim-check` 
  - `npm install` 
  - `ng serve --open`
- The local host server will open after compilation.

## Functionality and Usage
- Click on the “Let’s get started!” button on the introduction page.
- You will be routed to the Login Page.
- If you have an account already, type your login credentials. If not, click on  “Don’t have an account?” and register by typing your name, email, username and password. Confirm your password. After successful registration, you will be directed to the login page. Enter your login credentials and hit the “Login” button.
- After successful registration, you will be routed to the main page. The main page features your profile details and has a button for file upload, which leads you to the File Upload Page, a button to View your previous results and one for editing your profile.
- On clicking the “File Upload” button you’ll be directed to a page for uploading your file(s). After successfully uploading your file(s) (this may take a little time if your file size is big enough), you’ll have to click on the “View Results'' button, to view results in the form of various graphs and visualizations. 
- There’ll be a button on the “View Result” page that directs you to the main home page. 


## Project Plan Ahead
We would majorily be working to implement the core logic in the next half of the evaluation and would be following these steps in a coherent manner. 

We’ll start off with text preprocessing by removing the blank lines, comments, variable tokenization, etc.
- Divide the document into n-grams and hash these n-grams.
- Make windows of certain length over the hash values. In each window select the minimum hash value (There are several subtle variations. One has been stated here). If there is more than one hash with the minimum value, select the rightmost occurrence. 
- Now save all selected hashes as the signature vector for the document.
- Normalize the signature vectors after padding and measure their cosine similarity pairwise. 

## The Bigger Picture
We plan to implement the following bonus features
### Language Specific Functionality for C++
- Making our tool more robust to c++
- Will try to make functions inline (except recursive ones).
- Count the number of simple blocks, number of control edges, number of critical control edges, etc.

### Stub code
Dealing with the stub-code and “removing” its influence over the signature vector.


>>>>>>> f8702cf97ebf435a779800777ee074d5d953da66
