 # Red Plag
![GitHub repo size](https://img.shields.io/github/repo-size/scottydocs/README-template.md)
![GitHub contributors](https://img.shields.io/github/contributors/scottydocs/README-template.md)

Red Plag is a plagiarism checker tool that allows user to detect source code plagiarism and locate the instances of plagiarism within the code files pairwise. The frontend is implemented in Angular and backend with Django and Django REST framework.

It gives a visual measure of plagiarized content using scatter plots and also highlights the similar blocks between the files pairwise. It implements language-specific functionality to develop a more robust checker for Java.

## Prerequisites

Before you begin, ensure you have installed the latest version of the following:

* `python`
* `pygments`, a syntax package in `python`
* `Java`
* `@angular/cli`
* `Django`
* `Django REST`

## Installing Red Plag

To install **Red Plag**, follow these steps:

* Clone this github repository on your local machine using:
```bash
$ git clone https://github.com/tantheta01/Plagiarism-Detection
```
* Navigate to the `PYTORCH` directory, and setup the backend environment using:
```bash
$ cd Plagiarism-Detection/PYTORCH/
$ python3 manage.py runserver
```
* Navigate to the `FrontEnd` directory, and setup the frontend environment using:
```bash
$ cd ../FrontEnd/sim-check/
# install dependencies
$ npm install
$ ng serve --open
```
* The local host server will open after compilation.

## Using Red Plag

To use **Red Plag** follow these steps:
* Click on the *Let’s get started!* button on the introduction page.
* You will be routed to the login page. If you already have an account, login with those credentials. Else, click on *Don’t have an account?* and signup.
* Once logged in, the main page features options to change your password and upload the code files.
* Accepted File Format for Upload:
    * tar file format
    * on extracting, tar file should have two directories, namely `code_files` and `stub_files`.
    * `code_files` contains all the code files for pairwise plagiarism detection.
    * `stub_files` contains the stub code file(s) that is invariably common in all the code files.
* Upload the tar file in specified format.
* You will be navigated to the results page. The result page features the following:
    * Scatter plot to visualize high-dimensional signature vectors of the code files by performing dimensionality-reduction (**PCA**).
    * Highlighted similar blocks between the files pairwise.
    * A downloadable csv file `pairwise_similarity.csv` in the format:
    
| File 1         | File 2       | Similarity   |
| :------------- | :----------: | -----------: |

### Backend Endpoints
- `UserLogin`: An endpoint for logging in. Returns the username and the authentication token for the user.
- `UserCreate`: An endpoint for signing in. Returns the username and the email of the user.
- `PassChangeView`: An endpoint for changing password. Takes the old password and the new password of the user (authentication is done using token). If the old password matches the user's password, the password is updated.
- `FileUpload`: To upload the tarball. Takes the tar file to be uploaded and the authentication token of the user. Every file is linked to a user object and to facilitate organization and showing previous results, the file is saved at `/media/<username>/<filename>`.

## Contributors
* [@tantheta01](https://github.com/tantheta01)
* [@akshay-121](https://github.com/akshay-121)
* [@badola2320](https://github.com/badola2320)
* [@Liza23](https://github.com/Liza23)

## Contact
If you want to contact me you can reach me at greettanay@gmail.com.

## License
This project uses the following license: **MIT**.


## Project Plan Ahead
We would majorily be working to implement the core logic in the next half of the evaluation and would be following these steps in a coherent manner. 

We’ll start off with text preprocessing by removing the blank lines, variable tokenization.
- Divide the document into n-grams and hash the n-grams.
- Make windows of certain length over the hash values. In each window select the minimum hash value (There are several subtle variations. One has been stated here). If there is more than one hash with the minimum value, select the rightmost occurrence. 
- Now save all selected hashes as the signature vector for the document.
- Normalize the signature vectors after padding and measure their cosine similarity pairwise. 
- We are studying about tSNE and PCA for visualization of results
t-Distributed Stochastic Neighbor Embedding (t-SNE) is an unsupervised, non-linear technique primarily used for data exploration and visualizing high-dimensional data. In simpler terms, t-SNE gives you a feel or intuition of how the data is arranged in a high-dimensional space. 
