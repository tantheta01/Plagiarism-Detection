import { Component, OnInit, Input, ChangeDetectorRef } from '@angular/core';
import { FormControl, FormGroup, FormBuilder } from '@angular/forms';
import { CommunicationService } from 'src/app/communication.service';

@Component({
  selector: 'app-fileupload',
  templateUrl: './fileupload.component.html',
  styleUrls: ['./fileupload.component.css'],
})

export class FileUploadComponent implements OnInit {
  
  formGroup = this.fb.group({
    file: [null]
  });
  

  constructor(private commus: CommunicationService, private fb: FormBuilder, public cd : ChangeDetectorRef) { }

  ngOnInit() { }

  onFileChange(event) {
  let reader = new FileReader();
  console.log("ATEEE")
 
  if(event.target.files && event.target.files.length) {
    const [file] = event.target.files;
    // reader.readAsDataURL(file);
    this.formGroup.patchValue({
      file: file
    });
    console.log(JSON.stringify(this.formGroup.controls))
    // reader.onload = () => {
    //   this.formGroup.patchValue({
    //     file: reader.result
    //   });
      
    //   // need to run CD since file load runs outside of zone
    //   this.cd.markForCheck();
    // };
  }
}

  onSubmit() {
    // console.log(this.formGroup.controls['file'].value)
    // var httpOptions = {
    //   headers: new HttpHeaders({ 
    //     "Content-Type": "multipart/form-data",
    //     "Authorization": "Token " + this.commus.token
    //   }), 
    // };
    // this._http.post('http://localhost:8000/api/users/', {'test.cpp': this.fileUpload.controls['file'].value})
    this.commus.fileUpload(this.formGroup.controls['file'].value).subscribe({
      next: answer => {
        console.log(JSON.stringify(answer))
      },
      error: error => {
        console.log(JSON.stringify(error))
      }
    })
    // console.log(JSON.stringify(this.fileUpload.controls['file'].value))
  }
}