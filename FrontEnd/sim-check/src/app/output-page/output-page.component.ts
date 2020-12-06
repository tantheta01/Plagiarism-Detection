/*We need to add a download to this chart*/
import { Component, OnInit } from '@angular/core';
import { FormControl } from '@angular/forms';
import { ChartDataSets, ChartType, ChartOptions } from 'chart.js';
import { Label } from 'ng2-charts';
import {​​​​​​​​ DomSanitizer }​​​​​​​​ from '@angular/platform-browser';


@Component({
  selector: 'app-output-page',
  templateUrl: './output-page.component.html',
  styleUrls: ['./output-page.component.css']
})
export class OutputPageComponent implements OnInit {


  // panelOpenState=true;  
  fileUrl;
  public firstCode: any = JSON.parse(sessionStorage['datta']);
  public file_keys = Object.keys(this.firstCode);
  public fnames : any = sessionStorage['names'].split(',');
  public firstFile : string = this.fnames[0];
  public secondFile : string = this.fnames[1];
  firstFileControl = new FormControl(this.firstFile);
  secondFileControl = new FormControl(this.secondFile);
  public pairname: string = this.firstFileControl.value + ',' + this.secondFileControl.value;

  
  public scatterChartLabels: Label[] = ['Eating', 'Drinking', 'Sleeping', 'Designing', 'Coding', 'Cycling', 'Running'];


  public scatterChartData: ChartDataSets[] = [
    {
      data: [
        { x: 1, y: 1 },
        { x: 2, y: 3 },
        { x: 3, y: -2 },
        { x: 4, y: 4 },
        { x: 5, y: -3 },
      ],
      label: 'Series A',
      pointRadius: 10,
    },
  ];
  public scatterChartType: ChartType = 'scatter';
  public scatterChartOptions: ChartOptions = {
    responsive: true,
    title : {
      display : true,
      text: "The chart of my dreams",
    },
    tooltips: {
         callbacks: {
            label: function(tooltipItem, data) {
               var label = data.labels[tooltipItem.index];
               return label + ': (' + tooltipItem.xLabel + ', ' + tooltipItem.yLabel + ')';
            }
         }
      },
      scales: {
        xAxes: [{
            /* Your xAxes options here */
        }, {
            position: 'top',
            ticks: {
                display: false
            },
            gridLines: {
                display: false,
                drawTicks: false
            }
        }],
        yAxes: [{
            /* Your yAxes options here */
        }, {
            position: 'right',
            ticks: {
                display: false
            },
            gridLines: {
                display: false,
                drawTicks: false
            }
        }]
    }
  };



  constructor(private sanitizer: DomSanitizer) { }
  ngOnInit(){
    console.log(sessionStorage['embeddings'][0])
    console.log("bhodaaaa")
    const data = sessionStorage['csvfile'];
    const blob = new Blob([data], {​​​​​​​​ type: 'application/octet-stream' }​​​​​​​​);
    this.fileUrl = this.sanitizer.bypassSecurityTrustResourceUrl(window.URL.createObjectURL(blob));


    console.log("Init occurs");
    console.log(this.firstCode['f2.py,f.py']["first_file"]);

    console.log(this.fnames);

    for (var i = 0; i < this.file_keys.length; ++i) {
      var fCdd = this.firstCode[this.file_keys[i]]['first_file'];
      // console
      if (fCdd.substring(0, 6) == "<mark>") {
        var j=1;
        var bstring = fCdd.split("<mark>");
        console.log(bstring.length)
        console.log("is the BString length of the shitttttt")
        var bits=[];
        console.log("The length of Bstring is");
        console.log(bstring.length);
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j ^= 1;
        }
        this.firstCode[this.file_keys[i]]['first_file'] = bstring;
        this.firstCode[this.file_keys[i]]['first_params'] = bits;
      }
      else{
        var j=0;
        var bstring = fCdd.split("<mark>");
        console.log("The length of Bstring hereere is");
        console.log(bstring.length);
        console.log(this.file_keys[i]);
        // console.log(bstring);
        var bits=[];
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j = (j+1)%2;
        }
        this.firstCode[this.file_keys[i]]['first_file'] = bstring;
        this.firstCode[this.file_keys[i]]['first_params'] = bits;
      }
      fCdd = this.firstCode[this.file_keys[i]]['second_file'];
      if (fCdd.substring(0, 6) == "<mark>") {
        var j=1;
        var bstring = fCdd.split("<mark>");
        var bits=[];
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j = (j+1)%2;
        }
        this.firstCode[this.file_keys[i]]['second_file'] = bstring;
        this.firstCode[this.file_keys[i]]['second_params'] = bits;
      }
      else{
        var j=0;
        var bstring = fCdd.split("<mark>");
        var bits=[];
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j ^= 1;
        }
        this.firstCode[this.file_keys[i]]['second_file'] = bstring;
        this.firstCode[this.file_keys[i]]['second_params'] = bits;
      }
    }



  }
  public chartClicked({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }

  public FileNameChange(event): void {
    this.pairname = this.firstFileControl.value + ',' + this.secondFileControl.value;
    console.log("this is such a dhit ititititi");
  }

  public chartHovered({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }


}