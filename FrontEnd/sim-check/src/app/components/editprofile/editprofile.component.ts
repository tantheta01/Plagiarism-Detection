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
		name : new FormControl(''),
		email : new FormControl(''),
		username : new FormControl(''),
    old_password : new FormControl('', [Validators.required]),
    new_password : new FormControl('', [Validators.required]),
  })

  constructor(public cservice : CommunicationService) { }

  ngOnInit(): void {
  }

  onSubmit() {
    if (this.userDetails.valid) {
      this.cservice.changepass(this.userDetails.controls['new_password'].value).subscribe({
        next : answer => {
          window.alert(JSON.stringify(answer));
        },
        error: error => {
          JSON.stringify(error);
        }
      })
    }
  }

}
