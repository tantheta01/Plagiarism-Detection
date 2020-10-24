import { NgModule, CUSTOM_ELEMENTS_SCHEMA } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { AngularMaterialModule } from './angular-material.module';
import { AppRoutingModule } from './app-routing.module';
import { FlexLayoutModule } from "@angular/flex-layout";
import { AppComponent } from './app.component';
import { LogInComponent } from './components/login/login.component';
import { RegisterComponent } from './components/register/register.component';
import { GetstartedComponent } from './components/getstarted/getstarted.component';
import { MainpageComponent } from './components/mainpage/mainpage.component';
import { EditprofileComponent } from './components/editprofile/editprofile.component';
import {
  HttpClientModule,
  
} from "@angular/common/http";


@NgModule({
  declarations: [
    AppComponent,
    LogInComponent,
    RegisterComponent,
    GetstartedComponent,
    MainpageComponent,
    EditprofileComponent,

  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    FormsModule, ReactiveFormsModule,
    AngularMaterialModule,
    AppRoutingModule,
    FlexLayoutModule,
    HttpClientModule,
    
  ],
  providers: [],
  bootstrap: [AppComponent],
  schemas: [CUSTOM_ELEMENTS_SCHEMA]
})

export class AppModule { }