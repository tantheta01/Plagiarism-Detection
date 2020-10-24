import { Injectable } from '@angular/core';
import { Observable, throwError } from "rxjs";
import {
  HttpClient,
  HttpHeaders,
  HttpErrorResponse,
  HttpParams
} from "@angular/common/http";
import { catchError, map } from "rxjs/operators";


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
	username: string = '';
	password: string = '';
	email : string = '';
	token : string = '';



  constructor(private httpClient : HttpClient) {  }

  	signUp(uname: string, passwd : string, email: string): Observable<any> {
  		
  		// return from(fetch(signUpurl, {}))
		return this.httpClient.post(signUpurl, {
			'username' : uname, 
			'password' : passwd, 
			'email' : email
		} , httpOptions);
	}

	login(uname : string, passwd : string): Observable<any>{
		
		return this.httpClient.post(loginurl, {
			'username' : uname,
			'password' : passwd
		}, httpOptions);
	}

	changepass(newpass : string): Observable<any>{
		if (this.isLoggedin) {
			const httpOptions_ = { headers: new HttpHeaders({ "Content-Type" : "multipart/form-data", "Authorization" : "Token " + this.token })}

			return this.httpClient.post(passchange, {'newpassword' : newpass}, httpOptions_)
		}
	}
	
}
