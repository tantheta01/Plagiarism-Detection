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

  
  public scatterChartLabels: Label[] = this.fnames;

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
      text: "File Embeddings",
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


  public scatterChartLabels2: Label[];
  

  public scatterChartData2: ChartDataSets[];
  public scatterChartType2: ChartType = 'bar';
  public scatterChartOptions2: ChartOptions = {
    responsive: true,
    title : {
      display : true,
      text: "Number of pairs V/S Similarity",
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

    // console.log(sessionStorage['embeddings'])
    var J = sessionStorage['embeddings'].split(',')
    var detaa = [];
    for(var i=0;i<J.length;i=i+2){
      detaa.push({
        x : parseFloat(J[i]),
        y : parseFloat(J[i+1])
      });
    }
    this.scatterChartData = [
          {
            data : detaa,
            label: 'SeriesA',
            pointRadius: 10
          },
    ];
    J = sessionStorage['range_sim'].split(',')
    detaa = []
    for(var i=0;i<J.length;i++){
      detaa.push(parseFloat(J[i]));
    }
    this.scatterChartLabels2 = ['less than 0.2', 'between 0.2 and 0.4', 'between 0.4 and 0.6', 'between 0.6 and 0.8', 'more than 0.8'];
    this.scatterChartData2 = [{data: detaa, label: 'Number of Files'}]




    console.log("bhodaaaa")
    const data = sessionStorage['csvfile'];
    const parsed_data = JSON.parse(data);

    const file1 = String(parsed_data[0]).split(',');
    const file2 = String(parsed_data[1]).split(',');
    const similarity = String(parsed_data[2]).split(',');

    var csv = "File1,File2,Similarity";
    const n = file1.length;
    for (let i = 0; i < n; i++) {
      csv += '\n';
      csv += String(file1[i]) + "," + String(file2[i]) + "," + String(similarity[i]);
    }
    
    const blob = new Blob([csv], {​​​​​​​​ type: 'application/octet-stream' }​​​​​​​​);
    this.fileUrl = this.sanitizer.bypassSecurityTrustResourceUrl(window.URL.createObjectURL(blob));


    // console.log(this.fnames);

    for (var i = 0; i < this.file_keys.length; ++i) {
      var fCdd = this.firstCode[this.file_keys[i]]['first_file'];
      // console
      if (fCdd.substring(0, 6) == "<mark>") {
        var j=1;
        var bstring = fCdd.split("<mark>");
        // console.log(bstring.length)
        // console.log("is the BString length of the shitttttt")
        var bits=[];
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j ^= 1;
        }
        this.firstCode[this.file_keys[i]]['first_file'] = bstring;
        this.firstCode[this.file_keys[i]]['first_params'] = bits;
        // console.log(bits.length);
        // console.log("IS the length of bits")
        // console.log(this.file_keys[i]);
      }
      else {
        var j=0;
        var bstring = fCdd.split("<mark>");
        // console.log(bstring);
        var bits=[];
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j = (j+1)%2;
        }
        this.firstCode[this.file_keys[i]]['first_file'] = bstring;
        this.firstCode[this.file_keys[i]]['first_params'] = bits;
        // console.log(bits.length);
        // console.log("IS the length of bits")
        // console.log(this.file_keys[i]);
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
        // console.log(bits.length);
        // console.log("IS the length of bits")
        // console.log(this.file_keys[i]);
      }
      else {
        var j=0;
        var bstring = fCdd.split("<mark>");
        var bits=[];
        for(var k=0;k<bstring.length;k++){
          bits.push(j);
          j ^= 1;
        }
        this.firstCode[this.file_keys[i]]['second_file'] = bstring;
        this.firstCode[this.file_keys[i]]['second_params'] = bits;
        // console.log(bits.length);
        // console.log("IS the length of bits");
        // console.log(this.file_keys[i]);
      }
    }

  }

  public chartClicked({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }

  public FileNameChange(event): void {
    this.pairname = this.firstFileControl.value + ',' + this.secondFileControl.value;
  }

  public chartHovered({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }

}
