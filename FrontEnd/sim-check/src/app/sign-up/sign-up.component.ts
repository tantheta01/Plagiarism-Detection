import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';

import { CommunicationService } from '../communication.service';

@Component({
  selector: 'app-sign-up',
  templateUrl: './sign-up.component.html',
  styleUrls: ['./sign-up.component.css']
})

export class SignUpComponent implements OnInit {
	keys : any=3;
	userSignupForm = new FormGroup({
		name : new FormControl('', [Validators.required]),
		username : new FormControl('', [Validators.required]),
		email : new FormControl('', [Validators.required]),
		password : new FormControl('', [Validators.required]),
		confirm_password : new FormControl('', [Validators.required])
	})

	onSubmit() : void{
		this.commserv.signUp(this.userSignupForm.controls['username'].value, this.userSignupForm.controls['password'].value, this.userSignupForm.controls['email'].value).subscribe(ans => this.keys = Object.keys(ans));

		console.log('Aur BCEE');
	}
  constructor(private commserv : CommunicationService) { }

  ngOnInit(): void {
  }

}
