import { Component, OnInit, Input, ChangeDetectorRef, ViewChild, ElementRef } from '@angular/core';
import { FormControl, FormGroup, FormBuilder } from '@angular/forms';
import { CommunicationService } from 'src/app/communication.service';
import { RouterLink, Router } from '@angular/router';
import Swal from 'sweetalert2';

@Component({
  selector: 'app-fileupload',
  templateUrl: './fileupload.component.html',
  styleUrls: ['./fileupload.component.css'],
})

export class FileUploadComponent implements OnInit {

  // @ViewChild("fileUpload", {static: false}) fileUpload: ElementRef;files = [];
  
  formGroup = this.fb.group({
    file: [null],
  });
  

  constructor(private commus: CommunicationService, private fb: FormBuilder, public cd : ChangeDetectorRef, private router : Router) { }

  ngOnInit() { }

  onFileChange(event) {
  
    let reader = new FileReader();
 
    if(event.target.files && event.target.files.length) {
      const [file] = event.target.files;
      // reader.readAsDataURL(file);
      this.formGroup.patchValue({
        file: file
      });    
    }

  }

  onSubmit() {
    
    this.commus.fileUpload(this.formGroup.controls['file'].value).subscribe({
      next: answer => {
        console.log("Oyeeeeee")
        console.log(answer.data[Object.keys(answer.data)[0]]);
        console.log(JSON.stringify(answer.csv))
        
        sessionStorage.setItem('datta', JSON.stringify(answer.data));
        sessionStorage.setItem('names', answer.names);
        sessionStorage.setItem("csvfile", JSON.stringify(answer.csv));

        sessionStorage.setItem('embeddings', answer.embeddings);
        sessionStorage.setItem('range_sim', answer.range_sim);
        console.log(answer.embeddings.length)
        console.log(sessionStorage['names']);
        this.router.navigate(['/outp']);
      },
      error: error => {
        console.log(JSON.stringify(error))
      }
    })

  }
  
}