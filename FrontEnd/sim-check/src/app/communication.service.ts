import { Inject, Injectable } from '@angular/core';
import { Observable, throwError, of } from "rxjs";
import {
  HttpClient,
  HttpHeaders,
  HttpErrorResponse,
  HttpParams
} from "@angular/common/http";
import { catchError, map } from "rxjs/operators";
import { Router } from '@angular/router';


const httpOptions = {
  headers: new HttpHeaders({ "Content-Type": "application/json"}), 
};


const signUpurl : string = 'http://localhost:8000/api/users/';
const loginurl : string = 'http://localhost:8000/api/users/login/';
const fileUploadurl : string = 'http://localhost:8000/api/files/upload/';
const passchange : string = 'http://localhost:8000/api/password/';


@Injectable({
  providedIn: 'root'
})


export class CommunicationService {

	isLoggedin: boolean = false;
	// username: string = '';
	// password: string = '';
	// email : string = '';
	// token : string = '';


  constructor(private httpClient : HttpClient, private router: Router) {  }

  	signUp(uname: string, passwd : string, email: string): Observable<any> {
  		
  		// return from(fetch(signUpurl, {}))
		return this.httpClient.post(signUpurl, {
			'username' : uname, 
			'password' : passwd, 
			'email' : email
		} , httpOptions);
	}

	login(uname : string, passwd : string): Observable<any> {
		
		return this.httpClient.post(loginurl, {
			'username' : uname,
			'password' : passwd
		}, httpOptions);
	}

	changepass(oldpass : string, newpass : string): Observable<any>{
		if (sessionStorage['token'] != null) {
			const httpOptions_ = { headers: new HttpHeaders({ "Content-Type" : "application/json", "Authorization" : "Token " + sessionStorage['token']})}

			return this.httpClient.put(passchange, {'old_password' : oldpass, 'new_password' : newpass}, httpOptions_)
		}
	}

	navigateToMain() {
		this.router.navigate(['/mainpage']);
	}

	navigateToLogin() {
		this.router.navigate(['/login']);
	}

	fileUpload(file: any): Observable<any> {
		var httpOptions1 = {
			headers: new HttpHeaders({ 
			  // "Content-Type": 'multipart/form-data',
			  "Authorization": "Token " + sessionStorage['token'],
			}),

		  };
		const formData: FormData = new FormData();
		formData.append('file', file);
		return this.httpClient
		  .post('http://localhost:8000/api/files/upload/' + file.name, formData, httpOptions1,)
		//   .map(() => { return true; })
		//   .catch((e) => this.handleError(e));
	}

}
