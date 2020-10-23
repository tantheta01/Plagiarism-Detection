import { NgModule, CUSTOM_ELEMENTS_SCHEMA } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
<<<<<<< HEAD
import { NgModule } from '@angular/core';
import { ReactiveFormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { ChartistModule } from 'ng-chartist';
import { HighchartsChartModule } from 'highcharts-angular';

=======
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { AngularMaterialModule } from './angular-material.module';
>>>>>>> 2d8adfe6dc8bd91d406a97656dea39b219fdf47d
import { AppRoutingModule } from './app-routing.module';
import { FlexLayoutModule } from "@angular/flex-layout";
import { AppComponent } from './app.component';
<<<<<<< HEAD
import { SignUpComponent } from './sign-up/sign-up.component';
import { LoginComponent } from './login/login.component';
import { ProfileComponent } from './profile/profile.component';
import { OutputPageComponent } from './output-page/output-page.component';
=======
import { LogInComponent } from './components/login/login.component';
import { RegisterComponent } from './components/register/register.component';
import { GetstartedComponent } from './components/getstarted/getstarted.component';
import { MainpageComponent } from './components/mainpage/mainpage.component';
import { EditprofileComponent } from './components/editprofile/editprofile.component';
>>>>>>> 2d8adfe6dc8bd91d406a97656dea39b219fdf47d

@NgModule({
  declarations: [
    AppComponent,
<<<<<<< HEAD
    SignUpComponent,
    LoginComponent,
    ProfileComponent,
    OutputPageComponent
=======
    LogInComponent,
    RegisterComponent,
    GetstartedComponent,
    MainpageComponent,
    EditprofileComponent,
>>>>>>> 2d8adfe6dc8bd91d406a97656dea39b219fdf47d
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    FormsModule, ReactiveFormsModule,
    AngularMaterialModule,
    AppRoutingModule,
<<<<<<< HEAD
    ReactiveFormsModule,
    HttpClientModule,
    ChartistModule,
    HighchartsChartModule
=======
    FlexLayoutModule
>>>>>>> 2d8adfe6dc8bd91d406a97656dea39b219fdf47d
  ],
  providers: [],
  bootstrap: [AppComponent],
  schemas: [CUSTOM_ELEMENTS_SCHEMA]
})

export class AppModule { }