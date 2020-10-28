import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, FormBuilder,  Validators } from '@angular/forms';
import { CommunicationService } from '../../communication.service';

@Component({
  selector: 'app-editprofile',
  templateUrl: './editprofile.component.html',
  styleUrls: ['./editprofile.component.css']
})
export class EditprofileComponent implements OnInit {

  userDetails = new FormGroup({
		old_password : new FormControl('', [Validators.required]),
		new_password : new FormControl('', [Validators.required]),
		confirm_newpassword : new FormControl('', [Validators.required]),
    
  })

  constructor(public cservice : CommunicationService) { }

  ngOnInit(): void {
  }

  onSubmit() {
    if (this.userDetails.valid) {
      console.log(sessionStorage['token']);
      this.cservice.changepass(this.userDetails.controls['old_password'].value, this.userDetails.controls['new_password'].value).subscribe({
        next : answer => {
          if(answer.status =="success"){
            window.alert("password changed successfully");
            this.cservice.navigateToMain();
          }
          else{
            window.alert("oops there was an error please try again");
            this.cservice.navigateToMain();
          }
        },
        error: error => {
          window.alert("oops there was an error. please try again");
          this.cservice.navigateToMain();
        }
      })
    }

    else{
      window.alert(this.userDetails.controls['new_password'].value + this.userDetails.controls['confirm_newpassword'].value)
    }
  }

}
