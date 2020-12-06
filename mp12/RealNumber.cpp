#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    /* Your code here */
    real_component = 0;
    magnitude = 0;
    phase = 0;
    number_type = REAL;
}

RealNumber::RealNumber(double rval)
{
    /* Your code here */
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval, 0);
    number_type = REAL;
}

RealNumber::RealNumber( const RealNumber& other )
{
    /* Your code here */
    real_component = other.get_real_component();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    number_type = other.get_number_type();
}

void RealNumber::set_real_component (double rval)
{
    /* Your code here */
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval, 0);
}

double RealNumber::get_real_component() const
{
    return real_component;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}
// 2 +-*/ 4
RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component / arg.get_real_component());
}
// 2 +- 4i
ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
    
    return ComplexNumber(real_component, + arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component, - arg.get_imaginary_component());
}
// 2 */ 4i
ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
    return ImaginaryNumber(real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
    return ImaginaryNumber(-1 * real_component / arg.get_imaginary_component());
}
// 2 +- <4,2>
ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), + arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), + arg.get_imaginary_component());
}
// 2 */ <4,2>
ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component * arg.get_real_component(), real_component * arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
    double den = (arg.get_real_component()*arg.get_real_component() + arg.get_imaginary_component()*arg.get_imaginary_component());
    double num_real = (real_component*arg.get_real_component());
    double num_imag = (real_component*-1*arg.get_imaginary_component());
    return ComplexNumber(num_real / den , num_imag / den);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}

