import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { GetstartedComponent } from './components/getstarted/getstarted.component';
import { LogInComponent } from './components/login/login.component';
import { RegisterComponent } from './components/register/register.component';
import { MainpageComponent } from './components/mainpage/mainpage.component';
import { EditprofileComponent } from './components/editprofile/editprofile.component';
import { MaterialFileUploadComponent } from './components/material-file-upload/material-file-upload.component';

const routes: Routes = [
  { path: '', pathMatch: 'full', redirectTo: 'getstarted' },
  { path: 'getstarted', component: GetstartedComponent },
  { path: 'login', component: LogInComponent },
  { path: 'register', component: RegisterComponent },
  { path: 'mainpage', component: MainpageComponent },
  { path: 'editprofile', component: EditprofileComponent },
  { path: 'upload', component: MaterialFileUploadComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule { }
