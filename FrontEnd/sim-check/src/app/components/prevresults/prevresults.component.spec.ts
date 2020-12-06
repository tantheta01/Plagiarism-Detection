import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { PrevresultsComponent } from './prevresults.component';

describe('PrevresultsComponent', () => {
  let component: PrevresultsComponent;
  let fixture: ComponentFixture<PrevresultsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ PrevresultsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(PrevresultsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
