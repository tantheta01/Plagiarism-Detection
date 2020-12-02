/*We need to add a download to this chart*/
import { Component, OnInit } from '@angular/core';

import { ChartDataSets, ChartType, ChartOptions } from 'chart.js';
import { Label } from 'ng2-charts';

@Component({
  selector: 'app-output-page',
  templateUrl: './output-page.component.html',
  styleUrls: ['./output-page.component.css']
})
export class OutputPageComponent implements OnInit {



  
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



  constructor() { }
  ngOnInit(){}
  public chartClicked({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }

  public chartHovered({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }

}