import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder, Validators } from '@angular/forms';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-log-in',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LogInComponent implements OnInit {

  userLoginForm = new FormGroup({
		username : new FormControl('', [Validators.required]),
		// email : new FormControl('', [Validators.required]),
		password : new FormControl('', [Validators.required]),
		// confirm_password : new FormControl('', [Validators.required])
  })
  
  // userLoginForm = this.fb.group({
  //   username : [, [Validators.required]],
	// 	email : [, [Validators.email, Validators.required]],
	// 	password : [, [Validators.required]],
	// 	confirm_password : [, [Validators.required]]
  // });

  constructor(private fb: FormBuilder) { }

  ngOnInit(): void {
  }

  onSubmit() {
    if (this.userLoginForm.valid) {
    }
    else window.alert("Submission failed!");
  }

}
