import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder, Validators } from '@angular/forms';
import { RouterLink } from '@angular/router';
import { CommunicationService } from '../../communication.service';



@Component({
  selector: 'app-log-in',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LogInComponent implements OnInit {

  userLoginForm = new FormGroup({
    username : new FormControl('', [Validators.required]),
    password : new FormControl('', [Validators.required]),

  })
  

  constructor(private fb: FormBuilder, public commus : CommunicationService) { }

  ngOnInit(): void {
  }

  onSubmit() {
    if (this.userLoginForm.valid) {

      this.commus.login(this.userLoginForm.controls['username'].value, this.userLoginForm.controls['password'].value).subscribe({
        next : answer => {
          this.commus.isLoggedin=true;
          this.commus.token=answer['token']
          this.commus.email=answer['email']
          this.commus.username=answer['username']
          this.commus.password=this.userLoginForm.controls['password'].value;
          window.alert("Logged in successfully")

        },
        error : error => {
          window.alert(JSON.stringify(error))
        }

      })


    }
    else window.alert("Submission failed!");
  }

}