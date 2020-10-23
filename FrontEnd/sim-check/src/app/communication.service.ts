import { Injectable } from '@angular/core';
import { Observable, throwError } from "rxjs";
import {
  HttpClient,
  HttpHeaders,
  HttpErrorResponse
} from "@angular/common/http";
import { catchError, map } from "rxjs/operators";


const httpOptions = {
  headers: new HttpHeaders({ "Content-Type": "application/json"})
};


const signUpurl : string = 'http://localhost:8000/api/users/';
const loginurl : string = 'http://localhost:8000/api/users/login/';
const fileUploadurl : string = 'http://localhost:8000/api/files/upload/';


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
  		var fd = new FormData();
  		fd.append('username', uname);
  		fd.append('password', passwd);
  		fd.append('email', email);
		return this.httpClient.post(signUpurl, fd, httpOptions);
	}

	login(uname : string, passwd : string): Observable<any>{
		var fd = new FormData();
		fd.append('username', uname);
		fd.append('password', passwd);
		return this.httpClient.post(loginurl, fd, httpOptions);
	}
	
}
