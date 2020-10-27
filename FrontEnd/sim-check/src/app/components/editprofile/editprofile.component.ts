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
      this.cservice.changepass(this.userDetails.controls['old_password'].value, this.userDetails.controls['new_password'].value).subscribe({
        next : answer => {
          window.alert(JSON.stringify(answer));
        },
        error: error => {
          window.alert(JSON.stringify(error));
        }
      })
    }

    else{
      window.alert(this.userDetails.controls['new_password'].value + this.userDetails.controls['confirm_newpassword'].value)
    }
  }

}
