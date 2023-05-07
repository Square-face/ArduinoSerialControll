int roundUp(double num) {
  int test = round(num);
  if ((test < num) && (num > 0)) {
    return test+1;
  } else if ((test > num) && (num < 0)){
    return test-1;
  }
  else{
    return test;
  }
}