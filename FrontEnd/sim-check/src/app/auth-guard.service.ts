import { Injectable, Inject } from '@angular/core';
import { CanActivate,CanActivateChild, ActivatedRouteSnapshot, RouterStateSnapshot, Router } from '@angular/router';

@Injectable({
  providedIn: 'root'
})
export class AuthGuard implements CanActivate,CanActivateChild {
  constructor(private router: Router) {}

  canActivate(
    next: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): boolean {
  	console.log(sessionStorage['username'])
    if(sessionStorage['username'] != null){
      return true;
    }
    this.router.navigate["/getstarted"];
    return false;
    // console.log("Heyy");
    // return true;
  }

   canActivateChild(
    next: ActivatedRouteSnapshot,
    state: RouterStateSnapshot): boolean {
    if(sessionStorage.getItem('bearer') != null){
      return true;
    }
    this.router.navigate["/getstarted"];
    return false;
  }
}