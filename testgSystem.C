// josie 15 mar 2024
// test of using gSystem->Exec() to get current directory (if there is a one-line way to read the current directory as a string - I think there is not) 

string getpwdstring();

void testgSystem(){

  string pwdstring;

  gSystem->Exec("pwd > pwd.out");
  ifstream pwdf;
  pwdf.open("pwd.out");

  pwdf >> pwdstring;
  cout << "pwd: " << pwdstring << endl;

  pwdf.close();

  // again! but as a function
  string pwdstring2 = getpwdstring();

  cout << "pwd with function: " << pwdstring2 << endl;
}

string getpwdstring(){
  string returnstring;
  gSystem->Exec("pwd > pwd.out");
  ifstream inpwd;
  inpwd.open("pwd.out");
  inpwd >> returnstring;
  inpwd.close();

  return returnstring;
}
