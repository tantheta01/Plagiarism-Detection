import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder, Validators } from '@angular/forms';
import { RouterLink, Router } from '@angular/router';
import { CommunicationService } from '../../communication.service';
import Swal from 'sweetalert2';


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
  hide : boolean = false;
  

  constructor(private fb: FormBuilder, public commus : CommunicationService, private router : Router) { }

  ngOnInit(): void {
  }

  onSubmit() {

    if (this.userLoginForm.valid) {
      // var unam = this.userLoginForm.controls['username'].value;
      // var pass = this.userLoginForm.controls['password'].value;
      this.commus.login(this.userLoginForm.controls['username'].value, this.userLoginForm.controls['password'].value).subscribe({
        next : answer => {
          // localStorage.setItem('username' , unam);
          // localStorage.setItem('password', pass);
          sessionStorage.setItem('username', answer['username']);
          sessionStorage.setItem('token', answer['token']);
          Swal.fire('Welcome', "Login Successful", 'success');

          this.router.navigate(['/mainpage'])
        },
        error : error => {
          Swal.fire("Oops", "Incorrect credentials", "error");
        }
      })

    }

    else Swal.fire('Oops', 'Something went wrong', 'error');
  
  }

}