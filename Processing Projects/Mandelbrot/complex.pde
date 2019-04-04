class complex {
  double real;
  double imag;
  
  complex(double real, double imaginary) {
    this.real = real;
    this.imag = imaginary;
  }
  complex mult(complex c) {
    return new complex(this.real * c.real - this.imag * c.imag,
        this.real * c.imag + this.imag * c.real);
  }
  complex add(complex c) {
    return new complex(this.real + c.real, this.imag + c.imag);
  }
  boolean lt(int i) {
    return this.abs() < i;
  }
  boolean gt(int i) {
    return this.abs() > i;
  }
  double abs() {
    return Math.sqrt(this.real * this.real + this.imag + this.imag);
  }
}
