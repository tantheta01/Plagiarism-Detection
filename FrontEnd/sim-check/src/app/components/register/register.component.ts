import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder, Validators } from '@angular/forms';

import { CommunicationService } from '../../communication.service';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})

export class RegisterComponent implements OnInit {


  userSignupForm = new FormGroup({
    name : new FormControl('', Validators.required),
		username : new FormControl('', [Validators.required]),
		email : new FormControl('', [Validators.required]),
		password : new FormControl('', [Validators.required]),
		confirm_password : new FormControl('', [Validators.required])
  })
  
  
  constructor(private fb: FormBuilder, public cservice : CommunicationService) { }

  ngOnInit() {
  }

  onSubmit() {
    if (this.userSignupForm.valid) {
      if(this.userSignupForm.controls['password'].value != this.userSignupForm.controls['confirm_password'].value){
        window.alert("Passwords do not match")
        this.userSignupForm.setValue({
          name : "",
          username : "",
          email : "",
          password : "",
          confirm_password : ""
        })

      }
      else{
        // window.alert("Naacho bc")
        // var new22=1;
        this.cservice.signUp(this.userSignupForm.controls['username'].value, this.userSignupForm.controls['password'].value, this.userSignupForm.controls['email'].value).subscribe(
        {
          next : answer => {
            window.alert("Registration Successful")
            this.cservice.navigateToLogin()
            JSON.stringify(answer)
          },
          error: error => {
            window.alert(JSON.stringify(error))
          }
        }
        )
      }
    }
    else window.alert("Submission failed!");
  }

}