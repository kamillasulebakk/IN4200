smooth_1D(double *v_new, double *v, int n, double c){
  for (int i=1; i<n-1; i++)
    v_new[i] = v[i] + c*(v[i-1]-2*v[i] + v[i+1]);
  v_new[0] = v[0];
  v_new[n-1] = v[n-1];
}

void smooth_2D(double **v, double **v_new, double c, int m, int n){
  for (int i=1; i<m-1; i++){
    for (int j=1; j<n-1; j++){
      v_new[i][j] = v[i][j] + c*(v[i-1][j] + v[i][j-1] - 4*v[i][j] + v[i][j+1] + v[i+1][j])
    }
  }
  // v_new[]
}
