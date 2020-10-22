import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder, Validators } from '@angular/forms';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})

export class RegisterComponent implements OnInit {

  // Roles: any = ['Instructor', 'Student'];

  userSignupForm = new FormGroup({
    name : new FormControl('', Validators.required),
		username : new FormControl('', [Validators.required]),
		email : new FormControl('', [Validators.required]),
		password : new FormControl('', [Validators.required]),
		confirm_password : new FormControl('', [Validators.required])
  })
  
  // userSignupForm = this.fb.group({
  //   name : [, [Validators.required]],
  //   username : [, [Validators.required]],
	// 	email : [, [Validators.email, Validators.required]],
	// 	password : [, [Validators.required]],
	// 	confirm_password : [, [Validators.required]]
  // });

  constructor(private fb: FormBuilder) { }

  ngOnInit() {
  }

  onSubmit() {
    if (this.userSignupForm.valid) {}
    else window.alert("Submission failed!");
  }

}