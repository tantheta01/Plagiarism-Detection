import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder,  Validators } from '@angular/forms';

@Component({
  selector: 'app-edit-profile',
  templateUrl: './edit-profile.component.html',
  styleUrls: ['./edit-profile.component.css']
})
export class EditProfileComponent implements OnInit {

/*  user1 = this.fb.group({
    Name: [, [Validators.required]],
    email: [, [Validators.email, Validators.required]],
    Username: [,[Validators.required]],
    PassWord: [,Validators.required],
    Gender: [,Validators.required],
    Institution: [,Validators.required],
    Description: [],

  });

*/
  user = new FormGroup({
		Name : new FormControl('', [Validators.required]),
		email : new FormControl('', [Validators.required]),
		Username : new FormControl('', [Validators.required]),
    password : new FormControl('', [Validators.required]),
    Gender : new FormControl('', [Validators.required]),
    Institution : new FormControl('', [Validators.required]),
  })

  constructor(private fb: FormBuilder) { }

  ngOnInit(): void {
    
  }

  onSubmit(){

  }

}
