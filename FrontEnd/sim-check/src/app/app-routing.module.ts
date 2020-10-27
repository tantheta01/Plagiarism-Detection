import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { GetstartedComponent } from './components/getstarted/getstarted.component';
import { LogInComponent } from './components/login/login.component';
import { RegisterComponent } from './components/register/register.component';
import { MainpageComponent } from './components/mainpage/mainpage.component';
import { EditprofileComponent } from './components/editprofile/editprofile.component';
import { FileUploadComponent } from './components/fileupload/fileupload.component';


import { AuthGuard } from './auth/auth.guard';

const routes: Routes = [
  { path: '', pathMatch: 'full', redirectTo: 'getstarted' },
  { path: 'getstarted', component: GetstartedComponent },
  { path: 'login', component: LogInComponent },
  { path: 'register', component: RegisterComponent },
  { path: 'mainpage', component: MainpageComponent, canActivate : [AuthGuard] },
  { path: 'editprofile', component: EditprofileComponent, canActivate : [AuthGuard] },
  { path: 'fileupload', component: FileUploadComponent, canActivate : [AuthGuard] }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})

export class AppRoutingModule { }
