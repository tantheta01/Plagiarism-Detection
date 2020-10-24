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
		name : new FormControl('', [Validators.required]),
		email : new FormControl('', [Validators.required]),
		username : new FormControl('', [Validators.required]),
    password : new FormControl('', [Validators.required]),
    gender : new FormControl('', [Validators.required]),
  })

  constructor(public cservice : CommunicationService) { }

  ngOnInit(): void {
  }

  onSubmit() {
    if (this.userDetails.valid) {
      this.cservice.changepass(this.userDetails.controls['password'].value).subscribe({
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
