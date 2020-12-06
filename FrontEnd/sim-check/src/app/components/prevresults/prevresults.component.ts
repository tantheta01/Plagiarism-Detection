import { Component, OnInit } from '@angular/core';
import { CommunicationService } from '../../communication.service';
@Component({
  selector: 'app-prevresults',
  templateUrl: './prevresults.component.html',
  styleUrls: ['./prevresults.component.css']
})

export class PrevresultsComponent implements OnInit {

  constructor(private commus: CommunicationService) { }

  ngOnInit(): void {
  }

}
